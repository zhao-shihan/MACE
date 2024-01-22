namespace MACE::inline Simulation::inline Physics {

inline namespace Messenger {

template<TargetForMuoniumPhysics ATarget>
class MuoniumPhysicsMessenger;

} // namespace Messenger

inline namespace Process {

using namespace LiteralUnit::Length;

template<TargetForMuoniumPhysics ATarget>
MuoniumTransport<ATarget>::MuoniumTransport() :
    NonMoveableBase{},
    G4VContinuousProcess{"MuoniumTransport", fUserDefined},
    fTarget{&ATarget::Instance()},
    fMeanFreePath{200_nm},
    fManipulateAllSteps{false},
    fParticleChange{},
    fTransportStatus{TransportStatus::Unknown},
    fIsExitingTargetVolume{false} {
    pParticleChange = &fParticleChange;
    MuoniumPhysicsMessenger<ATarget>::Instance().AssignTo(this);
}

template<TargetForMuoniumPhysics ATarget>
auto MuoniumTransport<ATarget>::IsApplicable(const G4ParticleDefinition& particle) -> G4bool {
    return &particle == Muonium::Definition() or
           &particle == Antimuonium::Definition();
}

template<TargetForMuoniumPhysics ATarget>
auto MuoniumTransport<ATarget>::AlongStepDoIt(const G4Track& track, const G4Step&) -> G4VParticleChange* {
    fParticleChange.Initialize(track);
    switch (fTransportStatus) {
    case TransportStatus::Unknown:
        std23::unreachable();
        break;
    case TransportStatus::Decaying:
        // Do nothing
        break;
    case TransportStatus::InsideTargetVolume:
        ProposeRandomFlight(track);
        break;
    case TransportStatus::ExitingTargetVolume:
        // Don't do anything, wait for G4Navigator to update
        // just reset the flag
        fIsExitingTargetVolume = false;
        break;
    case TransportStatus::OutsideTargetVolume:
        if (track.GetMaterial()->GetState() != kStateGas) {
            fParticleChange.ProposeTrackStatus(fStopButAlive);
        }
        break;
    }
    return &fParticleChange;
}

template<TargetForMuoniumPhysics ATarget>
auto MuoniumTransport<ATarget>::GetContinuousStepLimit(const G4Track& track, G4double, G4double, G4double& safety) -> G4double {
    if (track.GetProperTime() >= track.GetDynamicParticle()->GetPreAssignedDecayProperTime()) {
        fTransportStatus = TransportStatus::Decaying;
        SetGPILSelection(NotCandidateForSelection);
        return safety;
    } else if (fTarget->VolumeContain(track.GetPosition())) {
        fTransportStatus = TransportStatus::InsideTargetVolume;
        return DBL_MIN;
    } else if (fIsExitingTargetVolume) {
        fTransportStatus = TransportStatus::ExitingTargetVolume;
        return DBL_MIN;
    } else {
        fTransportStatus = TransportStatus::OutsideTargetVolume;
        // in other material, could be extracted to another process in future
        if (track.GetMaterial()->GetState() == kStateGas) {
            SetGPILSelection(NotCandidateForSelection);
            return safety;
        } else {
            return DBL_MIN;
        }
    }
}

template<TargetForMuoniumPhysics ATarget>
auto MuoniumTransport<ATarget>::ProposeRandomFlight(const G4Track& track) -> void {
    using namespace PhysicalConstant;

    // 'cause the momentum, position, etc. violates much in this process, no easy way of using G4 tracking mechanism to manage this process.
    // Thus we do that ourselves. The decay time is pre-assigned and used for limiting the flight time, and the "true safety" is ensured by bool expr.

    // pre step point position
    const auto& initialPosition = track.GetPosition();
    // get the pre-assigned decay time to determine when the flight stops and then let G4 decay it
    const auto timeLimit = track.GetDynamicParticle()->GetPreAssignedDecayProperTime() - track.GetProperTime();
    // std dev of velocity of single direction
    const auto sigmaV = std::sqrt((k_Boltzmann * c_squared / muon_mass_c2) * track.GetMaterial()->GetTemperature());

    // the total flight length in this G4Step
    G4double trueStepLength = 0;
    // momentum direction
    auto direction = track.GetMomentumDirection();
    // velocity magnitude
    auto velocity = track.GetVelocity();
    // elapsed time of this flight
    G4double flightTime = 0;
    // current position in flight
    G4ThreeVector position;
    // displacement of this flight
    // using this displacement instead of track local position in flight for better numeric accuracy
    G4ThreeVector displacement = {0, 0, 0};
    // the free path of single flight step
    G4double freePath;
    // flag indicate that the flight was terminated by decay
    G4bool timeUp;
    // flag indicate that the flight was terminated by target boundary
    G4bool insideVolume;

    {
        // a much faster and good random engine
        Math::Random::Xoshiro256Plus xoshiro256Plus(G4Random::getTheEngine()->operator unsigned int());
        // standard 3D Gaussian distribution
        Math::Random::Gaussian3DDiagnoalFast<G4ThreeVector> standardGaussian3D;
        // do random flight
        do {
            // set free path
            freePath = Math::Random::ExponentialFast(fMeanFreePath)(xoshiro256Plus);
            // update flight length
            trueStepLength += freePath;
            // update time
            flightTime += freePath / velocity;
            // update displacement
            displacement += freePath * direction;
            // update current position
            position = initialPosition + displacement;
            // check space-time limit
            timeUp = (flightTime >= timeLimit);
            insideVolume = fTarget->VolumeContain(position);
            if (timeUp or not insideVolume) { break; }
            // check whether the end point inside material
            if (not fTarget->Contain(position, true)) { continue; }
            // if inside material update its velocity
            // set a gauss vector of sigma=1
            direction = standardGaussian3D(xoshiro256Plus);
            // get its length before multiply sigmaV
            velocity = direction.mag();
            // normalize direction vector
            direction *= 1 / velocity; // do not use CLHEP::Hep3Vector::operator/=(double).
            // get the exact velocity
            velocity *= sigmaV;
        } while (not fManipulateAllSteps);
    }

    // then do the final correction to fulfill the limit

    // Correction (dt, dl) contributed from time
    std::pair<G4double, G4double> finalStepCorrectionFromDecay = {0, 0};
    // evaluate the correction from time if needed
    if (timeUp) {
        // flight is break by decay
        // a tiny bit smaller correction ensuring the final value is little bit larger than decay time
        finalStepCorrectionFromDecay.first = std::nextafter(flightTime - timeLimit, -1.0);
        finalStepCorrectionFromDecay.second = velocity * finalStepCorrectionFromDecay.first;
    }

    // Correction (dt, dl) contributed from space
    std::pair<G4double, G4double> finalStepCorrectionFromEscape = {0, 0};
    // evaluate the correction from space if needed
    if (not insideVolume) {
        // flight is break by target boundary
        auto binaryMore = displacement;
        auto binaryLess = displacement - freePath * direction;
        auto binaryStep = freePath;
        do {
            auto binaryMid = (binaryMore + binaryLess) / 2;
            position = initialPosition + binaryMid;
            if (fTarget->VolumeContain(position)) {
                binaryLess = binaryMid;
            } else {
                binaryMore = binaryMid;
            }
            binaryStep /= 2;
        } while (binaryStep > 1_nm);
        // a bit smaller correction ensuring the final position is outside the volume
        // the std::nextafter ensures robustness under case of bad accuracy
        finalStepCorrectionFromEscape.second = std::nextafter((displacement - binaryMore).mag(), -1.0);
        finalStepCorrectionFromEscape.first = finalStepCorrectionFromEscape.second / velocity;
        // remember to inform the next step that we are at the boundary of target
        fIsExitingTargetVolume = true;
    }

    // take the larger correction
    const auto& finalStepCorrection = finalStepCorrectionFromDecay.second > finalStepCorrectionFromEscape.second ?
                                          finalStepCorrectionFromDecay :
                                          finalStepCorrectionFromEscape;

    // update flight length
    trueStepLength -= finalStepCorrection.second;
    // update time
    flightTime -= finalStepCorrection.first;
    // update displacement
    displacement -= finalStepCorrection.second * direction;
    // update current position
    position = initialPosition + displacement;

    // Propose particle change

    fParticleChange.ProposeTrueStepLength(trueStepLength);
    fParticleChange.ProposeMomentumDirection(direction);
    fParticleChange.ProposeVelocity(velocity);
    fParticleChange.ProposeProperTime(track.GetProperTime() + flightTime);
    fParticleChange.ProposePosition(position);
    fParticleChange.ProposeLocalTime(track.GetLocalTime() + flightTime);
}

} // namespace Process

} // namespace MACE::inline Simulation::inline Physics
