#include "Mustard/Env/BasicEnv.h++"
#include "MACE/SimTarget/Action/ActionInitialization.h++"
#include "MACE/SimTarget/Action/DetectorConstruction.h++"
#include "MACE/SimTarget/Analysis.h++"
#include "MACE/SimTarget/RunManager.h++"
#include "MACE/Simulation/Physics/StandardPhysicsList.h++"

#include "muc/utility"

namespace MACE::SimTarget {

RunManager::RunManager() :
    MPIRunManager{},
    fAnalysis{std::make_unique_for_overwrite<Analysis>()} {
    const auto verboseLevel{Mustard::Env::BasicEnv::Instance().VerboseLevel()};

    const auto physicsList{new StandardPhysicsList};
    physicsList->SetVerboseLevel(muc::to_underlying(verboseLevel));
    SetUserInitialization(physicsList);

    const auto detectorConstruction{new DetectorConstruction};
    detectorConstruction->SetCheckOverlaps(Mustard::Env::VerboseLevelReach<'I'>());
    SetUserInitialization(detectorConstruction);

    SetUserInitialization(new ActionInitialization);
}

RunManager::~RunManager() = default;

} // namespace MACE::SimTarget
