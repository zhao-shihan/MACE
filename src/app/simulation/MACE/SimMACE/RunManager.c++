#include "MACE/Compatibility/std23/to_underlying.h++"
#include "MACE/Env/BasicEnv.h++"
#include "MACE/SimMACE/Action/ActionInitialization.h++"
#include "MACE/SimMACE/Action/DetectorConstruction.h++"
#include "MACE/SimMACE/Analysis.h++"
#include "MACE/SimMACE/PhysicsList.h++"
#include "MACE/SimMACE/RunManager.h++"

namespace MACE::SimMACE {

RunManager::RunManager() :
    MPIRunManager{},
    fAnalysis{std::make_unique_for_overwrite<Analysis>()} {
    const auto verboseLevel{Env::BasicEnv::Instance().GetVerboseLevel()};

    const auto physicsList{new PhysicsList};
    physicsList->SetVerboseLevel(std23::to_underlying(verboseLevel));
    SetUserInitialization(physicsList);

    const auto detectorConstruction{new DetectorConstruction};
    detectorConstruction->SetCheckOverlaps(verboseLevel >= MACE::Env::VL::Verbose);
    SetUserInitialization(detectorConstruction);

    SetUserInitialization(new ActionInitialization);
}

RunManager::~RunManager() = default;

} // namespace MACE::SimMACE
