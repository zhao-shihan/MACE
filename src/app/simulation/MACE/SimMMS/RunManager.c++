#include "MACE/SimMMS/Action/ActionInitialization.h++"
#include "MACE/SimMMS/Action/DetectorConstruction.h++"
#include "MACE/SimMMS/Analysis.h++"
#include "MACE/SimMMS/RunManager.h++"
#include "MACE/Simulation/Physics/StandardPhysicsList.h++"

#include "Mustard/Env/BasicEnv.h++"

#include "muc/utility"

namespace MACE::SimMMS {

RunManager::RunManager() :
    MPIRunManager{},
    fAnalysis{std::make_unique_for_overwrite<Analysis>()} {

    SetUserInitialization(new StandardPhysicsList);

    const auto detectorConstruction{new DetectorConstruction};
    detectorConstruction->SetCheckOverlaps(Mustard::Env::VerboseLevelReach<'I'>());
    SetUserInitialization(detectorConstruction);

    SetUserInitialization(new ActionInitialization);
}

RunManager::~RunManager() = default;

} // namespace MACE::SimMMS
