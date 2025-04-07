#include "MACE/SimVeto/DefaultMacro.h++"
#include "MACE/SimVeto/RunManager.h++"
#include "MACE/SimVeto/SimVeto.h++"

#include "Mustard/Env/CLI/Geant4CLI.h++"
#include "Mustard/Env/MPIEnv.h++"
#include "Mustard/Extension/Geant4X/Interface/MPIExecutive.h++"
#include "Mustard/Utility/UseXoshiro.h++"

namespace MACE::SimVeto {

SimVeto::SimVeto() :
    Subprogram{"SimVeto", "Simulation of events in Cosmic Ray muon Veto (CRV)."} {}

auto SimVeto::Main(int argc, char* argv[]) const -> int {
    Mustard::Env::CLI::Geant4CLI<> cli;
    Mustard::Env::MPIEnv env{argc, argv, cli};

    Mustard::UseXoshiro<512> random;
    cli.SeedRandomIfFlagged();

    // PhysicsList, DetectorConstruction, ActionInitialization are instantiated in RunManager constructor.
    // Mutually exclusive random seeds are distributed to all processes upon each BeamOn.
    RunManager runManager;
    Mustard::Geant4X::MPIExecutive{}.StartSession(cli, defaultMacro);

    return EXIT_SUCCESS;
}

} // namespace MACE::SimVeto
