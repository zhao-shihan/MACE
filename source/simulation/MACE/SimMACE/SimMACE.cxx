#include "MACE/Environment/CLI/BasicCLI.hxx"
#include "MACE/Environment/MPIEnvironment.hxx"
#include "MACE/SimMACE/Action/DetectorConstruction.hxx"
#include "MACE/SimMACE/Action/PhysicsList.hxx"
#include "MACE/SimMACE/RunManager.hxx"
#include "MACE/SimulationG4/MPIExecutive.hxx"

#include "Randomize.hh"

int main(int argc, char* argv[]) {
    MACE::Environment::CLI::BasicCLI cli;
    MACE::Environment::MPIEnvironment mpiEnvironment(argc, argv, cli);

    bool interactive = (argc == 1);

    CLHEP::MTwistEngine randEng(4357);
    G4Random::setTheEngine(&randEng);

    // DetectorConstruction, PhysicsList, ActionInitialization are instantiated in RunManager constructor.
    MACE::SimMACE::RunManager runManager;
    runManager.GetDetectorConstruction().SetCheckOverlaps(interactive ? true : false);
    runManager.GetPhysicsList().SetVerboseLevel(interactive ? 1 : 0);

    MACE::SimulationG4::MPIExecutive mpiExecutive;
    if (interactive) {
        mpiExecutive.StartInteractiveSession(argc, argv, "init_vis.mac");
    } else {
        mpiExecutive.StartBatchSession(argv[1]);
    }

    return EXIT_SUCCESS;
}
