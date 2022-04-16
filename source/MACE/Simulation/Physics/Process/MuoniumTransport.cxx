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
    fParticleChange(),
    fMeanFreePath(0.2_um),
    fFlightLimit(50_um),
    fCase(-1) {}

G4VParticleChange* MuoniumTransport::AlongStepDoIt(const G4Track& track, const G4Step& step) {
    fParticleChange.Initialize(track);
    if (fCase == 0) {
        ProposeRandomFlight(track.GetProperTime(),
                            track.GetPosition(),
                            track.GetVelocity(),
                            track.GetMomentumDirection(),
                            track.GetMaterial()->GetTemperature(),
                            step.GetStepLength());
    } else if (fCase == 2) {
        fParticleChange.ProposeTrackStatus(fStopButAlive);
    }
    return std::addressof(fParticleChange);
}

void MuoniumTransport::ProposeRandomFlight(const G4double& initialTime,
                                           const G4ThreeVector& initialPosition,
                                           const G4double& initialVelocity,
                                           const G4ThreeVector& initialDirection,
                                           const G4double& temperature,
                                           const G4double& trueStepLimit) {
    // elapsed time of the flight
    G4double flightTime = 0;
    // displacement of the flight
    G4ThreeVector displacement(0, 0, 0);
    // velocity magnitude
    auto velocity = initialVelocity;
    // velocity direction
    auto direction = initialDirection;
    // std dev of velocity of single direction
    const auto sigmaV = std::sqrt((k_Boltzmann * c_squared / muon_mass_c2) * temperature);
    // the random engine in use
    auto* const randEng = G4Random::getTheEngine();
    // the total flight length in this G4Step
    G4double flightLength = 0;
    // flight length of the single flight step
    G4double freePath;

    while (flightLength < trueStepLimit and fTarget->VolumeContains(initialPosition + displacement)) {
        if (fTarget->Contains(initialPosition + displacement)) {
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
        // update time
        flightTime += freePath / velocity;
        // update displacement
        displacement += freePath * direction;
        // update flight length
        flightLength += freePath;
    }

    fParticleChange.ProposeProperTime(initialTime + flightTime);
    fParticleChange.ProposePosition(initialPosition + displacement);
    fParticleChange.ProposeVelocity(velocity);
    fParticleChange.ProposeMomentumDirection(direction);
}

G4double MuoniumTransport::GetContinuousStepLimit(const G4Track& track, G4double, G4double, G4double& safety) {
    if (fTarget->VolumeContains(track.GetPosition())) {
        fCase = 0;
        return std::min(fFlightLimit, safety);
    } else if (track.GetMaterial()->GetState() == kStateGas) {
        fCase = 1;
        SetGPILSelection(NotCandidateForSelection);
        return safety;
    } else {
        fCase = 2;
        return 0;
    }
}

} // namespace MACE::Simulation::Physics::Process
