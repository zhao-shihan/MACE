#include "MACE/Simulation/SimMACE/Action/ActionInitialization.hxx"
#include "MACE/Simulation/SimMACE/Action/PhysicsList.hxx"
#include "MACE/Simulation/SimMACE/Analysis.hxx"
#include "MACE/Simulation/SimMACE/RunManager.hxx"

namespace MACE::Simulation::SimMACE {

RunManager::RunManager() :
    G4MPIRunManager() {
    SetUserInitialization(new DetectorConstruction());
    SetUserInitialization(new PhysicsList());
    SetUserInitialization(new ActionInitialization());
    // need to create an instance of Analysis ahead of time,
    // otherwise AnalysisMessenger won't work!
    Analysis::Instance();
}

} // namespace MACE::Simulation::SimMACE
