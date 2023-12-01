#include "MACE/Compatibility/std2b/to_underlying.h++"
#include "MACE/Env/BasicEnv.h++"
#include "MACE/SimTarget/Action/ActionInitialization.h++"
#include "MACE/SimTarget/Action/DetectorConstruction.h++"
#include "MACE/SimTarget/Analysis.h++"
#include "MACE/SimTarget/PhysicsList.h++"
#include "MACE/SimTarget/RunManager.h++"

namespace MACE::SimTarget {

RunManager::RunManager() :
    MPIRunManager{},
    fAnalysis{std::make_unique_for_overwrite<Analysis>()} {
    const auto verboseLevel{Env::BasicEnv::Instance().GetVerboseLevel()};

    const auto physicsList{new PhysicsList};
    physicsList->SetVerboseLevel(std2b::to_underlying(verboseLevel));
    SetUserInitialization(physicsList);

    const auto detectorConstruction{new DetectorConstruction};
    detectorConstruction->SetCheckOverlaps(verboseLevel >= MACE::Env::VL::Verbose);
    SetUserInitialization(detectorConstruction);

    SetUserInitialization(new ActionInitialization);
}

} // namespace MACE::SimTarget
