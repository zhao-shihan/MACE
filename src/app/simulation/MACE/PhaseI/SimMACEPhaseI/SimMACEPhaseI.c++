#include "MACE/Env/MPIEnv.h++"
#include "MACE/Extension/Geant4X/Interface/MPIExecutive.h++"
#include "MACE/PhaseI/SimMACEPhaseI/DefaultMacro.h++"
#include "MACE/PhaseI/SimMACEPhaseI/RunManager.h++"
#include "MACE/Utility/UseXoshiro.h++"

#include "Randomize.hh"

using namespace MACE;

auto main(int argc, char* argv[]) -> int {
    Env::CLI::Geant4CLI cli;
    Env::MPIEnv env{argc, argv, cli};

    UseXoshiro<512> random;
    cli.SeedRandomIfFlagged();

    // PhysicsList, DetectorConstruction, ActionInitialization are instantiated in RunManager constructor.
    // Mutually exclusive random seeds are distributed to all processes upon each BeamOn.
    PhaseI::SimMACEPhaseI::RunManager runManager;
    Geant4X::MPIExecutive{}.StartSession(cli, PhaseI::SimMACEPhaseI::defaultMacro);

    return EXIT_SUCCESS;
}
