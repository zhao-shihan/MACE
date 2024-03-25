#include "MACE/Compatibility/std23/to_underlying.h++"
#include "MACE/Env/BasicEnv.h++"
#include "MACE/SimTarget/Action/ActionInitialization.h++"
#include "MACE/SimTarget/Action/DetectorConstruction.h++"
#include "MACE/SimTarget/Analysis.h++"
#include "MACE/SimTarget/RunManager.h++"
#include "MACE/Simulation/Physics/StandardPhysicsList.h++"

namespace MACE::SimTarget {

RunManager::RunManager() :
    MPIRunManager{},
    fAnalysis{std::make_unique_for_overwrite<Analysis>()} {
    const auto verboseLevel{Env::BasicEnv::Instance().VerboseLevel()};

    const auto physicsList{new StandardPhysicsList};
    physicsList->SetVerboseLevel(std23::to_underlying(verboseLevel));
    SetUserInitialization(physicsList);

    const auto detectorConstruction{new DetectorConstruction};
    detectorConstruction->SetCheckOverlaps(Env::VerboseLevelReach<'I'>());
    SetUserInitialization(detectorConstruction);

    SetUserInitialization(new ActionInitialization);
}

RunManager::~RunManager() = default;

} // namespace MACE::SimTarget
