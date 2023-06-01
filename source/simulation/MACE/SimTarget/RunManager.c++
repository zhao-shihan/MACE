#include "MACE/SimTarget/Action/ActionInitialization.h++"
#include "MACE/SimTarget/Action/DetectorConstruction.h++"
#include "MACE/SimTarget/Analysis.h++"
#include "MACE/SimTarget/PhysicsList.h++"
#include "MACE/SimTarget/RunManager.h++"

namespace MACE::SimTarget {

RunManager::RunManager() :
    MPIRunManager(),
    fAnalysis(std::make_unique_for_overwrite<Analysis>()) {
    // Initialization
    SetUserInitialization(new PhysicsList);
    SetUserInitialization(new DetectorConstruction);
    SetUserInitialization(new ActionInitialization);
}

RunManager::~RunManager() = default;

} // namespace MACE::SimTarget
