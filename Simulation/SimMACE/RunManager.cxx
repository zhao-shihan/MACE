#include "SimMACE/RunManager.hxx"
#include "SimMACE/Physics/PhysicsList.hxx"
#include "SimMACE/Action/ActionInitialization.hxx"
#include "SimMACE/Utility/Analysis.hxx"

using namespace MACE::SimMACE;

RunManager::RunManager() :
    G4MPIRunManager() {
    SetUserInitialization(new DetectorConstruction());
    SetUserInitialization(new Physics::PhysicsList());
    SetUserInitialization(new ActionInitialization());
    // need to create an instance of Analysis ahead of time,
    // otherwise AnalysisMessenger won't work!
    Analysis::Instance();
}
