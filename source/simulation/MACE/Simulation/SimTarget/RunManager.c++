#include "MACE/Simulation/SimTarget/Action/ActionInitialization.h++"
#include "MACE/Simulation/SimTarget/Action/DetectorConstruction.h++"
#include "MACE/Simulation/SimTarget/Analysis.h++"
#include "MACE/Simulation/SimTarget/PhysicsList.h++"
#include "MACE/Simulation/SimTarget/RunManager.h++"

namespace MACE::inline Simulation::SimTarget {

RunManager::RunManager() :
    MPIRunManager(),
    fAnalysis(std::make_unique_for_overwrite<Analysis>()) {
    // Initialization
    SetUserInitialization(new PhysicsList);
    SetUserInitialization(new DetectorConstruction);
    SetUserInitialization(new ActionInitialization);
}

RunManager::~RunManager() = default;

} // namespace MACE::inline Simulation::SimTarget
