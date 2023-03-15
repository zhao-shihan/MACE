#include "MACE/Compatibility/std2b/to_underlying.hxx"
#include "MACE/Env/MPIEnv.hxx"
#include "MACE/Extension/CLHEPX/Random/Xoshiro256Engine.hxx"
#include "MACE/Extension/Geant4X/MPIExecutive.hxx"
#include "MACE/SimTarget/Action/DetectorConstruction.hxx"
#include "MACE/SimTarget/Action/PhysicsList.hxx"
#include "MACE/SimTarget/RunManager.hxx"

using namespace MACE;

int main(int argc, char* argv[]) {
    Env::CLI::Geant4CLI cli;
    Env::MPIEnv mpiEnv(argc, argv, cli);

    CLHEPX::Random::Xoshiro256Engine randomEngine(20030202);
    G4Random::setTheEngine(&randomEngine);

    const auto verboseLevel = cli.GetVerboseLevel().value_or(Env::VerboseLevel::Warning);

    // DetectorConstruction, PhysicsList, ActionInitialization are instantiated in RunManager constructor.
    SimTarget::RunManager runManager;
    SimTarget::Action::DetectorConstruction::Instance().SetCheckOverlaps(
        verboseLevel >= MACE::Env::VerboseLevel::Verbose ?
            true :
            false);
    SimTarget::Action::PhysicsList::Instance().SetVerboseLevel(
        std2b::to_underlying(verboseLevel));

    Geant4X::MPIExecutive().StartSession(cli, {
#include "MACE/SimTarget/DefaultInitialization.inlmac"
                                              });

    return EXIT_SUCCESS;
}
