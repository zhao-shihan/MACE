#include "MACE/Simulation/Physics/Process/MuoniumTransport.hxx"
#include "MACE/Utility/LiteralUnit.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include "Randomize.hh"

namespace MACE::Simulation::Physics::Process {

using namespace Utility::PhysicalConstant;
using namespace Utility::LiteralUnit;

MuoniumTransport::MuoniumTransport() :
    G4VContinuousProcess("MuoniumTransport", fTransportation),
    fTarget(std::addressof(Target::Instance())),
    fMeanFreePath(0.2_um),
    fFlightLimit(100_um),
    fCase(fUnknown),
    fParticleChange() {}

G4VParticleChange* MuoniumTransport::AlongStepDoIt(const G4Track& track, const G4Step& step) {
    fParticleChange.Initialize(track);
    switch (fCase) {
    case fUnknown:
        // Never
        break;
    case fInTargetVolume:
        ProposeRandomFlight(track, step);
        break;
    case fInVacuum:
        // Do nothing
        break;
    case fInCondensedMatter:
        fParticleChange.ProposeTrackStatus(fStopButAlive);
        break;
    }
    return std::addressof(fParticleChange);
}

void MuoniumTransport::ProposeRandomFlight(const G4Track& track, const G4Step& step) {
    // pre step point position
    const auto& initialPosition = track.GetPosition();
    // flight limit
    const auto trueStepLimit = step.GetStepLength();
    // std dev of velocity of single direction
    const auto sigmaV = std::sqrt((k_Boltzmann * c_squared / muon_mass_c2) * track.GetMaterial()->GetTemperature());
    // the random engine in use
    auto* const randEng = G4Random::getTheEngine();

    // the total flight length in this G4Step
    G4double flightLength = 0;
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
    G4ThreeVector currentPosition = initialPosition;
    // flight length of the single flight step
    G4double freePath;

    while (flightLength < trueStepLimit) {
        if (fTarget->Contains(currentPosition)) {
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
            // inside vacuum region of target fine structure,
            // stepping with mean free path at same velocity
            freePath = fMeanFreePath;
        }
        // update flight length
        flightLength += freePath;
        // update time
        flightTime += freePath / velocity;
        // update displacement
        displacement += freePath * direction;
        // update current position
        currentPosition = initialPosition + displacement;
        if (not fTarget->VolumeContains(currentPosition)) {
            break;
        }
    }

    fParticleChange.ProposeTrueStepLength(flightLength);
    fParticleChange.ProposeMomentumDirection(direction);
    fParticleChange.ProposeEnergy(((muon_mass_c2 / c_squared) / 2) * velocity * velocity);
    fParticleChange.ProposeVelocity(velocity);
    fParticleChange.ProposeProperTime(track.GetProperTime() + flightTime);
    fParticleChange.ProposePosition(currentPosition);
    fParticleChange.ProposeLocalTime(track.GetLocalTime() + flightTime);
}

G4double MuoniumTransport::GetContinuousStepLimit(const G4Track& track, G4double, G4double, G4double& safety) {
    if (fTarget->VolumeContains(track.GetPosition())) {
        fCase = fInTargetVolume;
        return std::min(fFlightLimit, safety);
    } else if (track.GetMaterial()->GetState() == kStateGas) {
        fCase = fInVacuum;
        return safety;
    } else {
        fCase = fInCondensedMatter;
        return 0;
    }
}

} // namespace MACE::Simulation::Physics::Process
