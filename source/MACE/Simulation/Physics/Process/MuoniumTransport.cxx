#include "MACE/Simulation/Physics/Process/MuoniumTransport.hxx"
#include "MACE/Utility/LiteralUnit.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include "Randomize.hh"

#include "Eigen/Core"

namespace MACE::Simulation::Physics::Process {

using namespace Utility::PhysicalConstant;
using namespace Utility::LiteralUnit;

MuoniumTransport::MuoniumTransport() :
    G4VContinuousProcess("MuoniumTransport", fTransportation),
    fTarget(std::addressof(Target::Instance())),
    fParticleChange(),
    fMeanFreePath(226_nm),
    fStepLimit(1_mm),
    fVacuumStepScale(2),
    fCase(-1) {}

G4double MuoniumTransport::GetContinuousStepLimit(const G4Track& track, G4double, G4double, G4double& safety) {
    // if (track.GetProperTime() >= track.GetDynamicParticle()->GetPreAssignedDecayProperTime()) {
    //     fCase = 0;
    //     SetGPILSelection(NotCandidateForSelection);
    //     return safety;
    // }
    if (fTarget->VolumeContains(track.GetPosition())) {
        fCase = 1;
        return std::min(fStepLimit, safety);
    } else if (track.GetMaterial()->GetState() == kStateGas) {
        fCase = 2;
        SetGPILSelection(NotCandidateForSelection);
        return safety;
    } else {
        fCase = 3;
        return 0;
    }
}

G4VParticleChange* MuoniumTransport::AlongStepDoIt(const G4Track& track, const G4Step& step) {
    fParticleChange.Initialize(track);
    if (fCase == 1) {
        const auto trueStepLimit = step.GetStepLength();
        if (trueStepLimit > 0) {
            ProposeRandomFlight(track.GetProperTime(),
                                track.GetPosition(),
                                track.GetVelocity(),
                                track.GetMomentumDirection(),
                                track.GetMaterial()->GetTemperature(),
                                trueStepLimit);
        }
    } else if (fCase == 3) {
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
    G4double deltaTime = 0;
    G4ThreeVector displacement(0, 0, 0);
    G4double velocity = initialVelocity;
    G4ThreeVector direction = initialDirection;
    const auto sigmaV = std::sqrt((k_Boltzmann * c_squared / muon_mass_c2) * temperature);

    G4double freePath;
    const auto vacuumStep = fVacuumStepScale * fMeanFreePath;

    do {
        if (fTarget->Contains(initialPosition + displacement)) {
            // sampling free path
            freePath = G4RandExponential::shoot(fMeanFreePath);
            // set a gauss vector of sigma=1
            direction.set(G4RandGauss::shoot(),
                          G4RandGauss::shoot(),
                          G4RandGauss::shoot());
            // get its length before multiply sigmaV
            velocity = direction.mag();
            // normalize direction vector
            direction /= velocity;
            // get the exact velocity
            velocity *= sigmaV;
            // update time
            deltaTime += freePath / velocity;
            // update displacement
            displacement += freePath * direction;
        } else {
            // inside vacuum region of target fine structure,
            // stepping with (fVacuumStepScale)*(fMeanFreePath) at same velocity
            deltaTime += vacuumStep / velocity;
            displacement += vacuumStep * direction;
        }
    } while (displacement.mag() < trueStepLimit);

    fParticleChange.ProposeProperTime(initialTime + deltaTime);
    fParticleChange.ProposePosition(initialPosition + displacement);
    fParticleChange.ProposeVelocity(velocity);
    fParticleChange.ProposeMomentumDirection(direction);
}

} // namespace MACE::Simulation::Physics::Process
