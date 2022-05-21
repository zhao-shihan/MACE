#include "MACE/Simulation/SimMACE/Action/DetectorConstruction.hxx"
#include "MACE/Simulation/SimMACE/Action/PhysicsList.hxx"
#include "MACE/Simulation/SimMACE/RunManager.hxx"

#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "Randomize.hh"

#include "mpi.h"

using namespace MACE::Simulation::SimMACE;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    bool visMode = (argc == 1);

    const auto randEng = std::make_unique<CLHEP::MTwistEngine>(4357L);
    G4Random::setTheEngine(randEng.get());

    // DetectorConstruction, PhysicsList, ActionInitialization are instantiated in RunManager constructor.
    const auto runManager = std::make_unique<RunManager>();
    runManager->GetDetectorConstruction().SetCheckOverlaps(visMode ? true : false);
    runManager->GetPhysicsList().SetVerboseLevel(visMode ? 1 : 0);

    auto* const uiManager = G4UImanager::GetUIpointer();
    if (visMode) {
        const auto uiExecutive = std::make_unique<G4UIExecutive>(argc, argv);
        const auto visExecutive = std::make_unique<G4VisExecutive>();
        visExecutive->Initialize();
        uiManager->ExecuteMacroFile("init_vis.mac");
        uiExecutive->SessionStart();
    } else {
        uiManager->ExecuteMacroFile(argv[1]);
    }

    MPI_Finalize();
    return EXIT_SUCCESS;
}
