#include "MACE/SimTarget/Action/ActionInitialization.hxx"
#include "MACE/SimTarget/Action/PhysicsList.hxx"
#include "MACE/SimTarget/Analysis.hxx"
#include "MACE/SimTarget/Messenger/GeometryMessenger.hxx"
#include "MACE/SimTarget/RunManager.hxx"

namespace MACE::SimTarget {

RunManager::RunManager() :
    MPIRunManager() {
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

} // namespace MACE::SimTarget
