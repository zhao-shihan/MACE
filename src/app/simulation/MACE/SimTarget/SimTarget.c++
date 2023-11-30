#include "MACE/Compatibility/std2b/to_underlying.h++"
#include "MACE/Env/MPIEnv.h++"
#include "MACE/Extension/CLHEPX/Random/Wrap.h++"
#include "MACE/Extension/Geant4X/MPIExecutive.h++"
#include "MACE/Math/Random/Generator/Xoshiro512SS.h++"
#include "MACE/SimTarget/Action/DetectorConstruction.h++"
#include "MACE/SimTarget/DefaultMacro.h++"
#include "MACE/SimTarget/PhysicsList.h++"
#include "MACE/SimTarget/RunManager.h++"

using namespace MACE;

int main(int argc, char* argv[]) {
    Env::CLI::Geant4CLI cli;
    Env::MPIEnv mpiEnv(argc, argv, cli);

    CLHEPX::Random::Wrap<Math::Random::Xoshiro512SS> randomEngine;
    G4Random::setTheEngine(&randomEngine);

    const auto verboseLevel = cli.GetVerboseLevel().value_or(Env::VerboseLevel::Warning);

    // PhysicsList, DetectorConstruction, ActionInitialization are instantiated in RunManager constructor.
    SimTarget::RunManager runManager;
    runManager.SetVerboseLevel(std2b::to_underlying(verboseLevel));
    SimTarget::DetectorConstruction::Instance()
        .SetCheckOverlaps(verboseLevel >= MACE::Env::VerboseLevel::Verbose);
    SimTarget::PhysicsList::Instance()
        .SetVerboseLevel(std2b::to_underlying(verboseLevel));

    Geant4X::MPIExecutive().StartSession(cli, SimTarget::defaultMacro);

    return EXIT_SUCCESS;
}
