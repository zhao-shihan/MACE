#include "FTFP_BERT.hh"
#include "Randomize.hh"
#include "G4RunManager.hh"
#include "G4MPImanager.hh"
#include "G4MPIsession.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "MACEGlobal.hh"
#include "detector/DetectorConstruction.hh"

// #include "useraction/MACEActionInitialization.hh"
// #include "physics/MACEEmStandardPhysics.hh"

int main(int argc, char** argv) {
    CLHEP::MTwistEngine randomEngine(4357L);
    G4Random::setTheEngine(&randomEngine);

    auto runManager = new G4RunManager();
    runManager->SetUserInitialization(new FTFP_BERT());
    runManager->SetUserInitialization(new MACE::DetectorConstruction());
    // runManager->SetUserInitialization(new MACEActionInitialization());

    if (argc == 1) {
        // Initialize visualization
        auto uiManager = G4UImanager::GetUIpointer();
        auto visExecutive = new G4VisExecutive();
        auto uiExecutive = new G4UIExecutive(argc, argv);
        visExecutive->Initialize();
        uiManager->ExecuteMacroFile("init_vis.mac");
        uiExecutive->SessionStart();
        delete uiExecutive;
        delete visExecutive;
    } else {
        // mpirun
        auto g4MPIManager = new G4MPImanager(argc, argv);
        runManager->SetVerboseLevel(0);
        g4MPIManager->GetMPIsession()->SessionStart();
        delete g4MPIManager;
    }

    delete runManager;
    return EXIT_SUCCESS;
}
