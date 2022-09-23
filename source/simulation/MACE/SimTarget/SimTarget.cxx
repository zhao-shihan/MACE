#include "MACE/Environment/MPIEnvironment.hxx"
#include "MACE/Geant4X/MPIExecutive.hxx"
#include "MACE/SimTarget/Action/DetectorConstruction.hxx"
#include "MACE/SimTarget/Action/PhysicsList.hxx"
#include "MACE/SimTarget/RunManager.hxx"

#include "Randomize.hh"

#include <array>

int main(int argc, char* argv[]) {
    MACE::Environment::CLI::Geant4CLI cli;
    MACE::Environment::MPIEnvironment mpiEnvironment(argc, argv, cli);

    CLHEP::MTwistEngine randEng(4357);
    G4Random::setTheEngine(&randEng);

    // DetectorConstruction, PhysicsList, ActionInitialization are instantiated in RunManager constructor.
    MACE::SimTarget::RunManager runManager;
    MACE::SimTarget::Action::PhysicsList::Instance()
        .SetVerboseLevel(cli.IsInteractive() ? 1 : 0);
    MACE::SimTarget::Action::DetectorConstruction::Instance()
        .SetCheckOverlaps(cli.IsInteractive() ? true : false);

    MACE::Geant4X::MPIExecutive().StartSession(cli, std::array{
#include "MACE/SimTarget/DefaultInitialization.inlmac"
                                                    });

    return EXIT_SUCCESS;
}
