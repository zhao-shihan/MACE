#include "MACE/Simulation/Physics/Messenger/MuoniumPhysicsMessenger.hxx"
#include "MACE/Simulation/Physics/Particle/AntiMuonium.hxx"
#include "MACE/Simulation/Physics/Particle/Muonium.hxx"
#include "MACE/Simulation/Physics/Process/MuoniumTransport.hxx"
#include "MACE/Utility/LiteralUnit.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include "G4TransportationManager.hh"
#include "Randomize.hh"

namespace MACE::Simulation::Physics::Process {

using namespace Utility::PhysicalConstant;
using namespace Utility::LiteralUnit;

MuoniumTransport::MuoniumTransport() :
    G4VContinuousProcess("MuoniumTransport", fTransportation),
    fTarget(std::addressof(Target::Instance())),
    fMeanFreePath(200_nm),
    fManipulateAllSteps(false),
    fParticleChange(),
    fCase(kUnknown),
    fIsExitingTargetVolume(false) {
    pParticleChange = std::addressof(fParticleChange);
    Messenger::MuoniumPhysicsMessenger::Instance().SetTo(this);
}

G4bool MuoniumTransport::IsApplicable(const G4ParticleDefinition& particle) {
    return std::addressof(particle) == Particle::Muonium::Definition() or std::addressof(particle) == Particle::AntiMuonium::Definition();
}

G4VParticleChange* MuoniumTransport::AlongStepDoIt(const G4Track& track, const G4Step&) {
    fParticleChange.Initialize(track);
    switch (fCase) {
    case kUnknown:
        // Never
        break;
    case kDecaying:
        // Do nothing
        break;
    case kInsideTargetVolume:
        ProposeRandomFlight(track);
        break;
    case kExitingTargetVolume:
        // Don't do anything, wait for G4Navigator to update
        // just reset the flag
        fIsExitingTargetVolume = false;
        break;
    case kExitedTargetVolume:
        if (track.GetMaterial()->GetState() != kStateGas) {
            fParticleChange.ProposeTrackStatus(fStopButAlive);
        }
        break;
    }
    return std::addressof(fParticleChange);
}

G4double MuoniumTransport::GetContinuousStepLimit(const G4Track& track, G4double, G4double, G4double& safety) {
    if (track.GetProperTime() >= track.GetDynamicParticle()->GetPreAssignedDecayProperTime()) {
        fCase = kDecaying;
        SetGPILSelection(NotCandidateForSelection);
        return safety;
    } else if (fTarget->VolumeContains(track.GetPosition())) {
        fCase = kInsideTargetVolume;
        return DBL_MIN;
    } else if (fIsExitingTargetVolume) {
        fCase = kExitingTargetVolume;
        return DBL_MIN;
    } else {
        fCase = kExitedTargetVolume;
        // in other material, could be extracted to another process in future
        if (track.GetMaterial()->GetState() == kStateGas) {
            SetGPILSelection(NotCandidateForSelection);
            return safety;
        } else {
            return DBL_MIN;
        }
    }
}

void MuoniumTransport::ProposeRandomFlight(const G4Track& track) {
    // 'cause the momentum, position, etc. violates much in this process, no easy way of using G4 tracking mechanism to manage this process.
    // Thus we do that ourselves. The decay time is pre-assigned and used for limiting the flight time, and the "true safety" is ensured by bool expr.

    // the random engine in use
    auto* const randEng = G4Random::getTheEngine();
    // pre step point position
    const auto& initialPosition = track.GetPosition();
    // get the pre-assigned decay time to determine when the flight stops and then let G4 decay it
    const auto timeLimit = track.GetDynamicParticle()->GetPreAssignedDecayProperTime() - track.GetProperTime();
    // std dev of velocity of single direction
    const auto sigmaV = std::sqrt((k_Boltzmann * c_squared / muon_mass_c2) * track.GetMaterial()->GetTemperature());
    // the trial step in vacuum regions of target fine structure
    const auto stepInVacuum = 2 * fMeanFreePath;

    // the total flight length in this G4Step
    G4double trueStepLength = 0;
    // velocity magnitude
    G4double velocity = track.GetVelocity();
    // momentum direction
    G4ThreeVector direction = track.GetMomentumDirection();
    // elapsed time of the flight
    G4double flightTime = 0;
    // displacement of the flight
    // using this displacement instead of track local position in flight for better accuracy
    G4ThreeVector displacement(0, 0, 0);
    // current position in flight
    G4ThreeVector position = initialPosition;
    // the free path of single flight step
    G4double freePath;
    // the free time of single flight step
    G4double freeTime;
    // flag indicate that the flight was terminated by decay
    G4bool timeUp = false;
    // flag indicate that the flight was terminated by target boundary
    G4bool escaped = false;

    // do random flight

    do {
        if (fTarget->Contains(position)) {
            // sampling free path
            freePath = G4RandExponential::shoot(randEng, fMeanFreePath);
            // set a gauss vector of sigma=1
            direction.set(G4RandGauss::shoot(randEng),
                          G4RandGauss::shoot(randEng),
                          G4RandGauss::shoot(randEng));
            // get its length before multiply sigmaV
            velocity = direction.mag();
            // normalize direction vector
            direction /= velocity;
            // get the exact velocity
            velocity *= sigmaV;
        } else {
            // inside vacuum region of target fine structure
            freePath = stepInVacuum;
        }
        // calculate free time
        freeTime = freePath / velocity;
        // update flight length
        trueStepLength += freePath;
        // update time
        flightTime += freeTime;
        // update displacement
        displacement += freePath * direction;
        // update current position
        position = initialPosition + displacement;
        // check time
        timeUp = flightTime >= timeLimit;
        // check position
        escaped = not fTarget->VolumeContains(position);
    } while (not(timeUp or escaped or fManipulateAllSteps));

    // then do the final correction to fulfill the limit

    G4double finalStepFreePathCorrectionFromDecay = 0;
    G4double finalStepFreeTimeCorrectionFromDecay = 0;
    // evaluate the correction from time if needed
    if (timeUp) {
        // flight is break by decay
        // a tiny bit smaller correction ensuring the final value is little bit larger than decay time
        finalStepFreeTimeCorrectionFromDecay = std::nextafter(flightTime - timeLimit, -1.0);
        finalStepFreePathCorrectionFromDecay = velocity * finalStepFreeTimeCorrectionFromDecay;
    }

    G4double finalStepFreePathCorrectionFromEscape = 0;
    G4double finalStepFreeTimeCorrectionFromEscape = 0;
    // evaluate the correction from space if needed
    if (escaped) {
        // flight is break by target boundary
        G4ThreeVector binaryMore = displacement;
        G4ThreeVector binaryMid;
        G4ThreeVector binaryLess = displacement - freePath * direction;
        G4double binaryStep = freePath;
        do {
            binaryMid = (binaryMore + binaryLess) / 2;
            position = initialPosition + binaryMid;
            if (fTarget->VolumeContains(position)) {
                binaryLess = binaryMid;
            } else {
                binaryMore = binaryMid;
            }
            binaryStep /= 2;
        } while (binaryStep > 1_nm);
        // a bit smaller correction ensuring the final position is outside the volume
        // the std::nextafter ensures robustness under case of bad accuracy
        finalStepFreePathCorrectionFromEscape = std::nextafter((displacement - binaryMore).mag(), -1.0);
        finalStepFreeTimeCorrectionFromEscape = finalStepFreePathCorrectionFromEscape / velocity;
        // remember to inform the next step that we are at the boundary of target
        fIsExitingTargetVolume = true;
    }

    // the free time and free path correction of last step
    const auto finalStepFreePathCorrection = std::max(finalStepFreePathCorrectionFromDecay, finalStepFreePathCorrectionFromEscape);
    const auto finalStepFreeTimeCorrection = std::max(finalStepFreeTimeCorrectionFromDecay, finalStepFreeTimeCorrectionFromEscape);

    // update flight length
    trueStepLength -= finalStepFreePathCorrection;
    // update time
    flightTime -= finalStepFreeTimeCorrection;
    // update displacement
    displacement -= finalStepFreePathCorrection * direction;
    // update current position
    position = initialPosition + displacement;

    // Propose particle change

    fParticleChange.ProposeTrueStepLength(trueStepLength);
    fParticleChange.ProposeMomentumDirection(direction);
    fParticleChange.ProposeEnergy(((muon_mass_c2 / c_squared) / 2) * velocity * velocity);
    fParticleChange.ProposeVelocity(velocity);
    fParticleChange.ProposeProperTime(track.GetProperTime() + flightTime);
    fParticleChange.ProposePosition(position);
    fParticleChange.ProposeLocalTime(track.GetLocalTime() + flightTime);
}

} // namespace MACE::Simulation::Physics::Process
