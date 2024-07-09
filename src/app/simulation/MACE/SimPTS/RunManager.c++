#include "MACE/SimPTS/Action/ActionInitialization.h++"
#include "MACE/SimPTS/Action/DetectorConstruction.h++"
#include "MACE/SimPTS/Analysis.h++"
#include "MACE/SimPTS/PhysicsList.h++"
#include "MACE/SimPTS/RunManager.h++"

#include "Mustard/Env/BasicEnv.h++"
#include "Mustard/Utility/LiteralUnit.h++"

#include "muc/utility"

namespace MACE::SimPTS {

using namespace Mustard::LiteralUnit::Energy;

RunManager::RunManager() :
    MPIRunManager{},
    fAnalysis{std::make_unique_for_overwrite<Analysis>()} {
    const auto verboseLevel{Mustard::Env::BasicEnv::Instance().VerboseLevel()};

    const auto physicsList{new PhysicsList};
    physicsList->SetVerboseLevel(muc::to_underlying(verboseLevel));
    SetUserInitialization(physicsList);

    const auto detectorConstruction{new DetectorConstruction};
    detectorConstruction->SetCheckOverlaps(Mustard::Env::VerboseLevelReach<'I'>());
    SetUserInitialization(detectorConstruction);

    SetUserInitialization(new ActionInitialization);
}

RunManager::~RunManager() = default;

} // namespace MACE::SimPTS
