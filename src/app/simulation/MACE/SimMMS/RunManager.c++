#include "MACE/Env/BasicEnv.h++"
#include "MACE/SimMMS/Action/ActionInitialization.h++"
#include "MACE/SimMMS/Action/DetectorConstruction.h++"
#include "MACE/SimMMS/Analysis.h++"
#include "MACE/SimMMS/RunManager.h++"
#include "MACE/Simulation/Physics/StandardPhysicsList.h++"

#include "muc/utility"

namespace MACE::SimMMS {

RunManager::RunManager() :
    MPIRunManager{},
    fAnalysis{std::make_unique_for_overwrite<Analysis>()} {
    const auto verboseLevel{Env::BasicEnv::Instance().VerboseLevel()};

    const auto physicsList{new StandardPhysicsList};
    physicsList->SetVerboseLevel(muc::to_underlying(verboseLevel));
    SetUserInitialization(physicsList);

    const auto detectorConstruction{new DetectorConstruction};
    detectorConstruction->SetCheckOverlaps(Env::VerboseLevelReach<'I'>());
    SetUserInitialization(detectorConstruction);

    SetUserInitialization(new ActionInitialization);
}

RunManager::~RunManager() = default;

} // namespace MACE::SimMMS
