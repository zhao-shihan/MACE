#include "G4MPImanager.hh"
#include "G4MPIsession.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "Randomize.hh"

#include "SimMACE/Action/DetectorConstruction.hxx"
#include "SimMACE/Physics/PhysicsList.hxx"
#include "SimMACE/RunManager.hxx"

using namespace MACE::SimMACE;

int main(int argc, char** argv) {
    bool visMode = (argc == 1);

    CLHEP::MTwistEngine engine(4357L);
    G4Random::setTheEngine(std::addressof(engine));

    // DetectorConstruction, PhysicsList, ActionInitialization are instantiated in RunManager constructor.
    auto runManager = std::make_unique<RunManager>();
    runManager->GetDetectorConstruction().SetCheckOverlaps(visMode ? true : false);
    runManager->GetPhysicsList().SetVerboseLevel(visMode ? 1 : 0);

    if (visMode) {
        auto uiExecutive = std::make_unique<G4UIExecutive>(argc, argv);
        auto visExecutive = std::make_unique<G4VisExecutive>();
        visExecutive->Initialize();
        G4UImanager::GetUIpointer()->ExecuteMacroFile("init_vis.mac");
        uiExecutive->SessionStart();
    } else {
        auto g4MPIManager = std::make_unique<G4MPImanager>(argc, argv);
        runManager->SetG4MPImanager(*g4MPIManager);
        g4MPIManager->GetMPIsession()->SessionStart();
    }

    return EXIT_SUCCESS;
}
