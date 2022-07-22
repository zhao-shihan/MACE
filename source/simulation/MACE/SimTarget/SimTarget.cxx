#include "MACE/Environment/MPIEnvironment.hxx"
#include "MACE/SimTarget/Action/DetectorConstruction.hxx"
#include "MACE/SimTarget/Action/PhysicsList.hxx"
#include "MACE/SimTarget/RunManager.hxx"
#include "MACE/SimulationG4/MPIExecutive.hxx"

#include "Randomize.hh"

int main(int argc, char* argv[]) {
    MACE::Environment::MPIEnvironment mpiEnvironment(argc, argv, std::nullopt);

    bool interactive = (argc == 1);

    CLHEP::MTwistEngine randEng(4357);
    G4Random::setTheEngine(&randEng);

    // DetectorConstruction, PhysicsList, ActionInitialization are instantiated in RunManager constructor.
    const auto runManager = std::make_unique<MACE::SimTarget::RunManager>();
    runManager->GetDetectorConstruction().SetCheckOverlaps(interactive ? true : false);
    runManager->GetPhysicsList().SetVerboseLevel(interactive ? 1 : 0);

    const auto mpiExecutive = std::make_unique<MACE::SimulationG4::MPIExecutive>();
    if (interactive) {
        mpiExecutive->StartInteractiveSession(argc, argv, "init_vis.mac");
    } else {
        mpiExecutive->StartBatchSession(argv[1]);
    }

    return EXIT_SUCCESS;
}
