#include "MACE/Simulation/SimEMC/Action/ActionInitialization.h++"
#include "MACE/Simulation/SimEMC/Action/DetectorConstruction.h++"
#include "MACE/Simulation/SimEMC/Analysis.h++"
#include "MACE/Simulation/SimEMC/PhysicsList.h++"
#include "MACE/Simulation/SimEMC/RunManager.h++"

namespace MACE::inline Simulation::SimEMC {

RunManager::RunManager() :
    MPIRunManager(),
    fAnalysis(std::make_unique_for_overwrite<Analysis>()) {
    // Initialization
    SetUserInitialization(new PhysicsList);
    SetUserInitialization(new DetectorConstruction);
    SetUserInitialization(new ActionInitialization);
}

RunManager::~RunManager() = default;

} // namespace MACE::inline Simulation::SimEMC
