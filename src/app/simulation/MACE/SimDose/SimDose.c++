#include "MACE/SimDose/DefaultMacro.h++"
#include "MACE/SimDose/RunManager.h++"
#include "MACE/SimDose/SimDose.h++"

#include "Mustard/Env/CLI/Geant4CLI.h++"
#include "Mustard/Env/CLI/Module/Geant4ReferencePhysicsListModule.h++"
#include "Mustard/Env/MPIEnv.h++"
#include "Mustard/Extension/Geant4X/Interface/MPIExecutive.h++"
#include "Mustard/Utility/UseXoshiro.h++"

namespace MACE::SimDose {

SimDose::SimDose() :
    Subprogram{"SimDose", "Simulation of absorbed dose in the Muonium-to-Antimuonium Conversion Experiment (MACE)."} {}

auto SimDose::Main(int argc, char* argv[]) const -> int {
    Mustard::Env::CLI::Geant4CLI<Mustard::Env::CLI::Geant4ReferencePhysicsListModule<"QBBC_EMZ">> cli;
    Mustard::Env::MPIEnv env{argc, argv, cli};

    Mustard::UseXoshiro<512> random;
    cli.SeedRandomIfFlagged();

    // PhysicsList, DetectorConstruction, ActionInitialization are instantiated in RunManager constructor.
    // Mutually exclusive random seeds are distributed to all processes upon each BeamOn.
    RunManager runManager{cli};
    Mustard::Geant4X::MPIExecutive{}.StartSession(cli, defaultMacro);

    return EXIT_SUCCESS;
}

} // namespace MACE::SimDose
