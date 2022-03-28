#include "Simulation/SimMACE/Action/ActionInitialization.hxx"
#include "Simulation/SimMACE/Physics/PhysicsList.hxx"
#include "Simulation/SimMACE/RunManager.hxx"
#include "Simulation/SimMACE/Utility/Analysis.hxx"

using MACE::Simulation::SimMACE::RunManager;
using MACE::Simulation::SimMACE::Utility::Analysis;

RunManager::RunManager() :
    G4MPIRunManager() {
    SetUserInitialization(new DetectorConstruction());
    SetUserInitialization(new Physics::PhysicsList());
    SetUserInitialization(new ActionInitialization());
    // need to create an instance of Analysis ahead of time,
    // otherwise AnalysisMessenger won't work!
    Analysis::Instance();
}
