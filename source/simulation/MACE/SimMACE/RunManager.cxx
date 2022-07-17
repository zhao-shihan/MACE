#include "MACE/SimMACE/Action/ActionInitialization.hxx"
#include "MACE/SimMACE/Action/PhysicsList.hxx"
#include "MACE/SimMACE/Analysis.hxx"
#include "MACE/SimMACE/RunManager.hxx"

namespace MACE::SimMACE {

RunManager::RunManager() :
    MPIRunManager() {
    SetUserInitialization(new DetectorConstruction());
    SetUserInitialization(new PhysicsList());
    SetUserInitialization(new ActionInitialization());
    // need to create an instance of Analysis ahead of time,
    // otherwise AnalysisMessenger won't work!
    Analysis::Instance();
}

} // namespace MACE::SimMACE
