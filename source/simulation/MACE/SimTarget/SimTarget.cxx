#include "MACE/Environment/MPIEnvironment.hxx"
#include "MACE/SimTarget/Action/DetectorConstruction.hxx"
#include "MACE/SimTarget/Action/PhysicsList.hxx"
#include "MACE/SimTarget/RunManager.hxx"
#include "MACE/SimulationG4/MPIExecutive.hxx"

#include "Randomize.hh"

#include <array>

int main(int argc, char* argv[]) {
    MACE::Environment::MPIEnvironment mpiEnvironment(argc, argv, std::nullopt);

    bool interactive = (argc == 1);

    CLHEP::MTwistEngine randEng(4357);
    G4Random::setTheEngine(&randEng);

    // DetectorConstruction, PhysicsList, ActionInitialization are instantiated in RunManager constructor.
    MACE::SimTarget::RunManager runManager;
    runManager.GetDetectorConstruction().SetCheckOverlaps(interactive ? true : false);
    runManager.GetPhysicsList().SetVerboseLevel(interactive ? 1 : 0);

    MACE::SimulationG4::MPIExecutive mpiExecutive;
    if (interactive) {
        mpiExecutive.StartInteractiveSession(argc, argv, std::array{
#include "MACE/SimTarget/DefaultInteractiveSessionInitialization.inlmac"
                                                         });
    } else {
        mpiExecutive.StartBatchSession(argv[1]);
    }

    return EXIT_SUCCESS;
}
