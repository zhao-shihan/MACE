#include "MACE/Compatibility/std23/to_underlying.h++"
#include "MACE/Env/BasicEnv.h++"
#include "MACE/SimEMC/Action/ActionInitialization.h++"
#include "MACE/SimEMC/Action/DetectorConstruction.h++"
#include "MACE/SimEMC/Analysis.h++"
#include "MACE/SimEMC/PhysicsList.h++"
#include "MACE/SimEMC/RunManager.h++"

namespace MACE::SimEMC {

RunManager::RunManager() :
    MPIRunManager{},
    fAnalysis{std::make_unique_for_overwrite<Analysis>()} {
    const auto verboseLevel{Env::BasicEnv::Instance().VerboseLevel()};

    const auto physicsList{new PhysicsList};
    physicsList->SetVerboseLevel(std23::to_underlying(verboseLevel));
    SetUserInitialization(physicsList);

    const auto detectorConstruction{new DetectorConstruction};
    detectorConstruction->SetCheckOverlaps(verboseLevel >= MACE::Env::VL::Verbose);
    SetUserInitialization(detectorConstruction);

    SetUserInitialization(new ActionInitialization);
}

RunManager::~RunManager() = default;

} // namespace MACE::SimEMC
