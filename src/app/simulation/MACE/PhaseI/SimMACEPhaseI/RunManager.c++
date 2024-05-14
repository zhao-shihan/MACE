#include "MACE/PhaseI/SimMACEPhaseI/Action/ActionInitialization.h++"
#include "MACE/PhaseI/SimMACEPhaseI/Action/DetectorConstruction.h++"
#include "MACE/PhaseI/SimMACEPhaseI/Analysis.h++"
#include "MACE/PhaseI/SimMACEPhaseI/PhysicsList.h++"
#include "MACE/PhaseI/SimMACEPhaseI/RunManager.h++"
#include "MACE/Compatibility/std23/to_underlying.h++"
#include "MACE/Env/BasicEnv.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::PhaseI::SimMACEPhaseI {

using namespace LiteralUnit::Energy;

RunManager::RunManager() :
    MPIRunManager{},
    fAnalysis{std::make_unique_for_overwrite<Analysis>()} {
    const auto verboseLevel{Env::BasicEnv::Instance().VerboseLevel()};

    const auto physicsList{new PhysicsList};
    physicsList->SetVerboseLevel(std23::to_underlying(verboseLevel));
    SetUserInitialization(physicsList);

    const auto detectorConstruction{new DetectorConstruction};
    detectorConstruction->SetCheckOverlaps(Env::VerboseLevelReach<'I'>());
    SetUserInitialization(detectorConstruction);

    SetUserInitialization(new ActionInitialization);
}

RunManager::~RunManager() = default;

} // namespace MACE::PhaseI::SimMACEPhaseI
