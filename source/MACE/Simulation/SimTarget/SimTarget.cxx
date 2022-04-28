#include "MACE/Simulation/SimTarget/Action/DetectorConstruction.hxx"
#include "MACE/Simulation/SimTarget/Action/PhysicsList.hxx"
#include "MACE/Simulation/SimTarget/RunManager.hxx"

#include "G4MPIsession.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "Randomize.hh"

using namespace MACE::Simulation::SimTarget;

int main(int argc, char** argv) {
    bool visMode = (argc == 1);

    // Known issue: use CLHEP::HepJamesRandom may cause dead lock!
    const auto randEng = std::make_unique<CLHEP::MTwistEngine>(4357L);
    G4Random::setTheEngine(randEng.get());

    // DetectorConstruction, PhysicsList, ActionInitialization are instantiated in RunManager constructor.
    const auto runManager = std::make_unique<RunManager>();
    runManager->GetDetectorConstruction().SetCheckOverlaps(visMode ? true : false);
    runManager->GetPhysicsList().SetVerboseLevel(visMode ? 1 : 0);

    if (visMode) {
        const auto uiExecutive = std::make_unique<G4UIExecutive>(argc, argv);
        const auto visExecutive = std::make_unique<G4VisExecutive>();
        visExecutive->Initialize();
        G4UImanager::GetUIpointer()->ExecuteMacroFile("init_vis.mac");
        uiExecutive->SessionStart();
    } else {
        const auto g4mpi = runManager->InitializeG4MPI(argc, argv);
        g4mpi->GetMPIsession()->SessionStart();
    }

    return EXIT_SUCCESS;
}
