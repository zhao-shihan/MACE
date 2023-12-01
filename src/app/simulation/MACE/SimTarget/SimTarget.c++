#include "MACE/Env/MPIEnv.h++"
#include "MACE/Extension/CLHEPX/Random/Wrap.h++"
#include "MACE/Extension/Geant4X/MPIExecutive.h++"
#include "MACE/Math/Random/Generator/Xoshiro512SS.h++"
#include "MACE/SimTarget/DefaultMacro.h++"
#include "MACE/SimTarget/RunManager.h++"

#include "Randomize.hh"

using namespace MACE;

auto main(int argc, char* argv[]) -> int {
    Env::CLI::Geant4CLI cli;
    Env::MPIEnv mpiEnv(argc, argv, cli);

    CLHEPX::Random::Wrap<Math::Random::Xoshiro512SS> randomEngine;
    G4Random::setTheEngine(&randomEngine);

    // PhysicsList, DetectorConstruction, ActionInitialization are instantiated in RunManager constructor.
    SimTarget::RunManager runManager;
    Geant4X::MPIExecutive().StartSession(cli, SimTarget::defaultMacro);

    return EXIT_SUCCESS;
}
