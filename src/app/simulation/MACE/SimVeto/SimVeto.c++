#include "MACE/SimVeto/DefaultMacro.h++"
#include "MACE/SimVeto/RunManager.h++"

#include "Mustard/Env/CLI/Geant4CLI.h++"
#include "Mustard/Env/MPIEnv.h++"
#include "Mustard/Extension/Geant4X/Interface/MPIExecutive.h++"
#include "Mustard/Utility/UseXoshiro.h++"

#include "Randomize.hh"

using namespace MACE;

auto main(int argc, char* argv[]) -> int {
    Mustard::Env::CLI::Geant4CLI<> cli;
    Mustard::Env::MPIEnv env{argc, argv, cli};

    Mustard::UseXoshiro<512> random;
    cli.SeedRandomIfFlagged();

    // PhysicsList, DetectorConstruction, ActionInitialization are instantiated in RunManager constructor.
    // Mutually exclusive random seeds are distributed to all processes upon each BeamOn.
    SimVeto::RunManager runManager;
    Mustard::Geant4X::MPIExecutive{}.StartSession(cli, SimVeto::defaultMacro);

    return EXIT_SUCCESS;
}
