#include "MACE/Simulation/SimTarget/Action/DetectorConstruction.hxx"
#include "MACE/Simulation/SimTarget/Action/PhysicsList.hxx"
#include "MACE/Simulation/SimTarget/RunManager.hxx"
#include "MACE/Simulation/Utility/MPIExecutive.hxx"

#include "Randomize.hh"

#include "mpi.h"

using namespace MACE::Simulation;

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    bool interactive = (argc == 1);

    const auto randEng = std::make_unique<CLHEP::MTwistEngine>(4357L);
    G4Random::setTheEngine(randEng.get());

    // DetectorConstruction, PhysicsList, ActionInitialization are instantiated in RunManager constructor.
    const auto runManager = std::make_unique<SimTarget::RunManager>();
    runManager->GetDetectorConstruction().SetCheckOverlaps(interactive ? true : false);
    runManager->GetPhysicsList().SetVerboseLevel(interactive ? 1 : 0);

    const auto mpiExecutive = std::make_unique<Utility::MPIExecutive>(argc, argv);
    if (interactive) {
        mpiExecutive->StartInteractiveSession("init_vis.mac");
    } else {
        mpiExecutive->StartBatchSession(argv[1]);
    }

    MPI_Finalize();
    return EXIT_SUCCESS;
}
