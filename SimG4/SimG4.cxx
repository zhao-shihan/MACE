#include "Randomize.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4MPImanager.hh"
#include "G4MPIsession.hh"

#include "SimG4/Physics/PhysicsList.hxx"
#include "SimG4/Action/DetectorConstruction.hxx"
#include "SimG4/Action/ActionInitialization.hxx"

using namespace MACE::SimG4;

int main(int argc, char** argv) {
    auto engine = new CLHEP::MTwistEngine(4357L);
    G4Random::setTheEngine(engine);

    auto runManager = new G4RunManager();
    runManager->SetUserInitialization(new Physics::PhysicsList());
    runManager->SetUserInitialization(new Action::DetectorConstruction());
    runManager->SetUserInitialization(new Action::ActionInitialization());

    if (argc == 1) {
        auto uiManager = G4UImanager::GetUIpointer();
        auto visExecutive = new G4VisExecutive();
        auto uiExecutive = new G4UIExecutive(argc, argv);
        visExecutive->Initialize();
        uiManager->ExecuteMacroFile("init_vis.mac");
        uiExecutive->SessionStart();
        delete uiExecutive;
        delete visExecutive;
    } else {
        auto g4MPIManager = new G4MPImanager(argc, argv);
        g4MPIManager->GetMPIsession()->SessionStart();
        delete g4MPIManager;
    }

    delete runManager;
    delete engine;

    return EXIT_SUCCESS;
}
