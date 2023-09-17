#include "MACE/Compatibility/std2b/to_underlying.h++"
#include "MACE/Env/MPIEnv.h++"
#include "MACE/Extension/CLHEPX/Random/Xoshiro512SSEngine.h++"
#include "MACE/Extension/Geant4X/MPIExecutive.h++"
#include "MACE/Simulation/SimTarget/Action/DetectorConstruction.h++"
#include "MACE/Simulation/SimTarget/PhysicsList.h++"
#include "MACE/Simulation/SimTarget/RunManager.h++"

using namespace MACE;

int main(int argc, char* argv[]) {
    Env::CLI::Geant4CLI cli;
    Env::MPIEnv mpiEnv(argc, argv, cli);

    CLHEPX::Random::Xoshiro512SSEngine randomEngine;
    G4Random::setTheEngine(&randomEngine);

    const auto verboseLevel = cli.GetVerboseLevel().value_or(Env::VerboseLevel::Warning);

    // PhysicsList, DetectorConstruction, ActionInitialization are instantiated in RunManager constructor.
    SimTarget::RunManager runManager;
    runManager.SetVerboseLevel(std2b::to_underlying(verboseLevel));
    SimTarget::DetectorConstruction::Instance()
        .SetCheckOverlaps(verboseLevel >= MACE::Env::VerboseLevel::Verbose);
    SimTarget::PhysicsList::Instance()
        .SetVerboseLevel(std2b::to_underlying(verboseLevel));

    Geant4X::MPIExecutive().StartSession(cli, {
#include "MACE/Simulation/SimTarget/DefaultInitialization.inlmac"
                                              });

    return EXIT_SUCCESS;
}
