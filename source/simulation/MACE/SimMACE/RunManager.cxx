#include "MACE/SimMACE/Action/ActionInitialization.hxx"
#include "MACE/SimMACE/Action/DetectorConstruction.hxx"
#include "MACE/SimMACE/Analysis.hxx"
#include "MACE/SimMACE/PhysicsList.hxx"
#include "MACE/SimMACE/RunManager.hxx"

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
