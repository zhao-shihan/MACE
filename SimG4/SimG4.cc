#include "FTFP_BERT.hh"
#include "G4EmStandardPhysics.hh"
#include "Randomize.hh"
#include "G4RunManager.hh"
#include "G4MPImanager.hh"
#include "G4VMPIseedGenerator.hh"
#include "G4MPIsession.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "physics/PhysicsList.hh"
#include "detector/DetectorConstruction.hh"
#include "action/ActionInitialization.hh"

using namespace MACE::SimG4;

G4RunManager* runManager;

void SetUserInitializations() {
    runManager->SetUserInitialization(new Physics::PhysicsList());
    runManager->SetUserInitialization(new DetectorConstruction());
    runManager->SetUserInitialization(new ActionInitialization());
}

int main(int argc, char** argv) {
    CLHEP::MTwistEngine randomEngine(4357L);
    G4Random::setTheEngine(&randomEngine);

    runManager = new G4RunManager();

    if (argc == 1) {
        SetUserInitializations();
        auto uiManager = G4UImanager::GetUIpointer();
        auto visExecutive = new G4VisExecutive();
        auto uiExecutive = new G4UIExecutive(argc, argv);
        visExecutive->Initialize();
        uiManager->ExecuteMacroFile("init_vis.mac");
        uiExecutive->SessionStart();
        delete uiExecutive;
        delete visExecutive;
    } else {
        // ! Construct G4MPImanager before construct PhysicsList to ensure
        //   the correct random behavior (processes has different seed).
        //
        //   See G4MPImanager::G4MPImanager(...)
        //       MACE::SimG4::Physics::MuoniumTransport::MuoniumTransport(...)
        //       MACE::SimMTransport::Track::SetSeed(...)
        //       MACE::SimMTransport::MonteCarlo::SetSeed(...)
        auto g4MPIManager = new G4MPImanager(argc, argv);
        SetUserInitializations();
        g4MPIManager->GetMPIsession()->SessionStart();
        delete g4MPIManager;
    }

    delete runManager;

    return EXIT_SUCCESS;
}
