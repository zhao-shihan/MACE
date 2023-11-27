#include "MACE/SimEMC/Action/ActionInitialization.h++"
#include "MACE/SimEMC/Action/DetectorConstruction.h++"
// #include "MACE/SimEMC/Analysis.h++"
#include "MACE/SimEMC/PhysicsList.h++"
#include "MACE/SimEMC/RunManager.h++"

namespace MACE::SimEMC {

RunManager::RunManager() :
    MPIRunManager() /* , */
/* fAnalysis(std::make_unique_for_overwrite<Analysis>()) */ {
    // Initialization
    SetUserInitialization(new PhysicsList);
    SetUserInitialization(new DetectorConstruction);
    SetUserInitialization(new ActionInitialization);
}

RunManager::~RunManager() = default;

} // namespace MACE::SimEMC
