#include "MACE/Simulation/SimTarget/Action/DetectorConstruction.hxx"
#include "MACE/Simulation/SimTarget/Action/PhysicsList.hxx"
#include "MACE/Simulation/SimTarget/RunManager.hxx"
#include "MACE/Utility/G4Util/MPIExecutive.hxx"
#include "MACE/Utility/MPIUtil/MainMPI.hxx"

#include "Randomize.hh"

using namespace MACE::Simulation;

int main_MPI(int argc, char* argv[]) {
    bool interactive = (argc == 1);

    const auto randEng = std::make_unique<CLHEP::MTwistEngine>(4357L);
    G4Random::setTheEngine(randEng.get());

    // DetectorConstruction, PhysicsList, ActionInitialization are instantiated in RunManager constructor.
    const auto runManager = std::make_unique<SimTarget::RunManager>();
    runManager->GetDetectorConstruction().SetCheckOverlaps(interactive ? true : false);
    runManager->GetPhysicsList().SetVerboseLevel(interactive ? 1 : 0);

    const auto mpiExecutive = std::make_unique<MACE::Utility::G4Util::MPIExecutive>(argc, argv);
    if (interactive) {
        mpiExecutive->StartInteractiveSession("init_vis.mac");
    } else {
        mpiExecutive->StartBatchSession(argv[1]);
    }

    return EXIT_SUCCESS;
}
