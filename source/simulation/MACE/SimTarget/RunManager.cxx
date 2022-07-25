#include "MACE/SimTarget/Action/ActionInitialization.hxx"
#include "MACE/SimTarget/Messenger/GeometryMessenger.hxx"
#include "MACE/SimTarget/RunManager.hxx"

namespace MACE::SimTarget {

using namespace Action;

RunManager::RunManager() :
    MPIRunManager(),
    fPhysicsList(new PhysicsList()),
    fAnalysis(std::make_unique<Analysis>()) {
    // Set actions
    SetUserInitialization(new DetectorConstruction());
    SetUserInitialization(fPhysicsList);
    SetUserInitialization(new ActionInitialization());
}

RunManager::~RunManager() = default;

} // namespace MACE::SimTarget
