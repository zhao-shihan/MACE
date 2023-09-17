#include "MACE/Simulation/SimMACE/Action/ActionInitialization.h++"
#include "MACE/Simulation/SimMACE/Action/DetectorConstruction.h++"
#include "MACE/Simulation/SimMACE/Analysis.h++"
#include "MACE/Simulation/SimMACE/PhysicsList.h++"
#include "MACE/Simulation/SimMACE/RunManager.h++"

namespace MACE::inline Simulation::SimMACE {

RunManager::RunManager() :
    MPIRunManager(),
    fAnalysis(std::make_unique_for_overwrite<Analysis>()) {
    // Initialization
    SetUserInitialization(new PhysicsList);
    SetUserInitialization(new DetectorConstruction);
    SetUserInitialization(new ActionInitialization);
}

RunManager::~RunManager() = default;

} // namespace MACE::inline Simulation::SimMACE
