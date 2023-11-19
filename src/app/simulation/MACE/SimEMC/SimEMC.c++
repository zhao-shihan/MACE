#include "MACE/Compatibility/std2b/to_underlying.h++"
#include "MACE/Env/MPIEnv.h++"
#include "MACE/Extension/CLHEPX/Random/Wrap.h++"
#include "MACE/Extension/Geant4X/MPIExecutive.h++"
#include "MACE/SimEMC/Action/DetectorConstruction.h++"
#include "MACE/SimEMC/PhysicsList.h++"
#include "MACE/SimEMC/RunManager.h++"

using namespace MACE;

auto main(int argc, char* argv[]) -> int {
    Env::CLI::Geant4CLI cli;
    Env::MPIEnv mpiEnv(argc, argv, cli);

    CLHEPX::Random::Wrap<Math::Random::Xoshiro512SS> randomEngine;
    G4Random::setTheEngine(&randomEngine);

    const auto verboseLevel = cli.GetVerboseLevel().value_or(Env::VerboseLevel::Warning);

    // PhysicsList, DetectorConstruction, ActionInitialization are instantiated in RunManager constructor.
    SimEMC::RunManager runManager;
    runManager.SetVerboseLevel(std2b::to_underlying(verboseLevel));
    SimEMC::DetectorConstruction::Instance()
        .SetCheckOverlaps(verboseLevel >= MACE::Env::VerboseLevel::Verbose);
    SimEMC::PhysicsList::Instance()
        .SetVerboseLevel(std2b::to_underlying(verboseLevel));

    Geant4X::MPIExecutive().StartSession(cli, {
#include "MACE/SimEMC/DefaultInitialization.inlmac"
                                              });

    return EXIT_SUCCESS;
}
