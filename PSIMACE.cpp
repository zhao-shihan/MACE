#include "userAction/PSIMACEDetectorConstruction.hh"
#include "userAction/PSIMACEActionInitialization.hh"

#include "FTFP_BERT.hh"
#include "physics/PSIMACEEmStandardPhysics.hh"

#include "G4MTRunManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "Randomize.hh"

int main(int argc, char* argv[]) {
    G4Random::setTheSeed(time(nullptr));

    auto runManager = new G4MTRunManager();
    auto physicsList = new FTFP_BERT();
    physicsList->RemovePhysics("G4EmStandard");
    physicsList->RegisterPhysics(new PSIMACEEmStandardPhysics());
    runManager->SetUserInitialization(physicsList);
    runManager->SetUserInitialization(new PSIMACEDetectorConstruction());
    runManager->SetUserInitialization(new PSIMACEActionInitialization());

    auto UImanager = G4UImanager::GetUIpointer();
    // Process macro or start UI session
    //
    if (argc == 1) {
        // Initialize visualization
        auto ui = new G4UIExecutive(argc, argv);
        auto visManager = new G4VisExecutive();
        visManager->Initialize();
        UImanager->ExecuteMacroFile("init_vis.mac");
        ui->SessionStart();
        delete ui;
        delete visManager;
    } else {
        // batch mode
        runManager->SetVerboseLevel(0);
        physicsList->SetVerboseLevel(0);
        UImanager->SetVerboseLevel(0);
        UImanager->ExecuteMacroFile(argv[1]);
    }

    delete runManager;
}
