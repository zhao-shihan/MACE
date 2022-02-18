#include "Randomize.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4MPImanager.hh"
#include "G4MPIsession.hh"

#include "SimMACE/Physics/PhysicsList.hxx"
#include "SimMACE/Action/DetectorConstruction.hxx"
#include "SimMACE/Action/ActionInitialization.hxx"

using namespace MACE::SimMACE;

int main(int argc, char** argv) {
    bool visMode = (argc == 1);

    auto engine = std::make_unique<CLHEP::MTwistEngine>(4357L);
    G4Random::setTheEngine(engine.get());

    auto runManager = std::make_unique<G4RunManager>();
    runManager->SetUserInitialization(new Physics::PhysicsList(visMode ? 1 : 0));
    runManager->SetUserInitialization(new Action::DetectorConstruction(visMode ? true : false));
    runManager->SetUserInitialization(new Action::ActionInitialization());

    if (visMode) {
        auto uiManager = G4UImanager::GetUIpointer();
        auto visExecutive = std::make_unique<G4VisExecutive>();
        auto uiExecutive = std::make_unique<G4UIExecutive>(argc, argv);
        visExecutive->Initialize();
        uiManager->ExecuteMacroFile("init_vis.mac");
        uiExecutive->SessionStart();
    } else {
        auto g4MPIManager = std::make_unique<G4MPImanager>(argc, argv);
        g4MPIManager->GetMPIsession()->SessionStart();
    }

    return EXIT_SUCCESS;
}
