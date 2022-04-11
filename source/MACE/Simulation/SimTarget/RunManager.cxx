#include "MACE/Simulation/SimTarget/ActionInitialization.hxx"
#include "MACE/Simulation/SimTarget/PhysicsList.hxx"
#include "MACE/Simulation/SimTarget/RunManager.hxx"
#include "MACE/Simulation/SimTarget/Utility/Analysis.hxx"

using MACE::Simulation::SimTarget::RunManager;
using MACE::Simulation::SimTarget::Utility::Analysis;

RunManager::RunManager() :
    G4MPIRunManager() {
    SetUserInitialization(new DetectorConstruction());
    SetUserInitialization(new PhysicsList());
    SetUserInitialization(new ActionInitialization());
    // need to create an instance of Analysis ahead of time,
    // otherwise AnalysisMessenger won't work!
    Analysis::Instance();
}
