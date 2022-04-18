#include "MACE/Simulation/SimTarget/Action/ActionInitialization.hxx"
#include "MACE/Simulation/SimTarget/Action/PhysicsList.hxx"
#include "MACE/Simulation/SimTarget/Analysis.hxx"
#include "MACE/Simulation/SimTarget/Messenger/GeometryMessenger.hxx"
#include "MACE/Simulation/SimTarget/RunManager.hxx"

namespace MACE::Simulation::SimTarget {

RunManager::RunManager() :
    G4MPIRunManager() {
    // Instantiate actions
    SetUserInitialization(new DetectorConstruction());
    SetUserInitialization(new PhysicsList());
    SetUserInitialization(new ActionInitialization());
    // Instantiate analysis
    Analysis::Instance();
    // Instantiate geometry messenger
    Messenger::GeometryMessenger::Instance();
}

RunManager::~RunManager() noexcept {
    Analysis::Instance().G4Quit();
}

} // namespace MACE::Simulation::SimTarget
