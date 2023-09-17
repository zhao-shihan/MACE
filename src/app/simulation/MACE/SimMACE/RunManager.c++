#include "MACE/SimMACE/Action/ActionInitialization.h++"
#include "MACE/SimMACE/Action/DetectorConstruction.h++"
#include "MACE/SimMACE/Analysis.h++"
#include "MACE/SimMACE/PhysicsList.h++"
#include "MACE/SimMACE/RunManager.h++"

namespace MACE::SimMACE {

RunManager::RunManager() :
    MPIRunManager(),
    fAnalysis(std::make_unique_for_overwrite<Analysis>()) {
    // Initialization
    SetUserInitialization(new PhysicsList);
    SetUserInitialization(new DetectorConstruction);
    SetUserInitialization(new ActionInitialization);
}

RunManager::~RunManager() = default;

} // namespace MACE::SimMACE
