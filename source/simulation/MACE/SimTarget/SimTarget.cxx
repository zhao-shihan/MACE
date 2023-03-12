#include "MACE/Env/MPIEnv.hxx"
#include "MACE/Extension/CLHEPX/Random/PCG32Engine.hxx"
#include "MACE/Extension/Geant4X/MPIExecutive.hxx"
#include "MACE/SimTarget/Action/DetectorConstruction.hxx"
#include "MACE/SimTarget/Action/PhysicsList.hxx"
#include "MACE/SimTarget/RunManager.hxx"

#include <array>

int main(int argc, char* argv[]) {
    MACE::Env::CLI::Geant4CLI cli;
    MACE::Env::MPIEnv mpiEnv(argc, argv, cli);

    MACE::CLHEPX::Random::PCG32Engine randomEngine(114514);
    G4Random::setTheEngine(&randomEngine);

    // DetectorConstruction, PhysicsList, ActionInitialization are instantiated in RunManager constructor.
    MACE::SimTarget::RunManager runManager;
    MACE::SimTarget::Action::PhysicsList::Instance()
        .SetVerboseLevel(cli.IsInteractive() ? 1 : 0);
    MACE::SimTarget::Action::DetectorConstruction::Instance()
        .SetCheckOverlaps(cli.IsInteractive() ? true : false);

    MACE::Geant4X::MPIExecutive().StartSession(cli, {
#include "MACE/SimTarget/DefaultInitialization.inlmac"
                                                    });

    return EXIT_SUCCESS;
}
