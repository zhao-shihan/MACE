#include "MACE/SimMACE/Action/ActionInitialization.hxx"
#include "MACE/SimMACE/RunManager.hxx"

namespace MACE::SimMACE {

using namespace Action;

RunManager::RunManager() :
    MPIRunManager(),
    fPhysicsList(new PhysicsList),
    fAnalysis(std::make_unique_for_overwrite<Analysis>()) {
    // Set actions
    SetUserInitialization(new DetectorConstruction);
    SetUserInitialization(fPhysicsList);
    SetUserInitialization(new ActionInitialization);
}

} // namespace MACE::SimMACE
