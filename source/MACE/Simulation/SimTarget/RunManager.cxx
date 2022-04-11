#include "MACE/Simulation/SimTarget/ActionInitialization.hxx"
#include "MACE/Simulation/SimTarget/Analysis.hxx"
#include "MACE/Simulation/SimTarget/PhysicsList.hxx"
#include "MACE/Simulation/SimTarget/RunManager.hxx"

namespace MACE::Simulation::SimTarget {

RunManager::RunManager() :
    G4MPIRunManager() {
    SetUserInitialization(new DetectorConstruction());
    SetUserInitialization(new PhysicsList());
    SetUserInitialization(new ActionInitialization());
    // need to create an instance of Analysis ahead of time,
    // otherwise AnalysisMessenger won't work!
    Analysis::Instance();
}

} // namespace MACE::Simulation::SimTarget
