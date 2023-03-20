#include "MACE/SimTarget/Action/ActionInitialization.hxx"
#include "MACE/SimTarget/Action/DetectorConstruction.hxx"
#include "MACE/SimTarget/Analysis.hxx"
#include "MACE/SimTarget/PhysicsList.hxx"
#include "MACE/SimTarget/RunManager.hxx"

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
