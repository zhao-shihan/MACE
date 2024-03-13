#include "MACE/Env/MPIEnv.h++"
#include "MACE/Extension/Geant4X/MPIExecutive.h++"
#include "MACE/SimMACE/DefaultMacro.h++"
#include "MACE/SimMACE/RunManager.h++"
#include "MACE/Utility/UseXoshiro.h++"

#include "Randomize.hh"

using namespace MACE;

auto main(int argc, char* argv[]) -> int {
    Env::CLI::Geant4CLI cli;
    Env::MPIEnv mpiEnv(argc, argv, cli);

    const auto random{UseXoshiro<512>()};
    cli.SeedRandomIfSet();

    // PhysicsList, DetectorConstruction, ActionInitialization are instantiated in RunManager constructor.
    SimMACE::RunManager runManager;
    Geant4X::MPIExecutive().StartSession(cli, SimMACE::defaultMacro);

    return EXIT_SUCCESS;
}
