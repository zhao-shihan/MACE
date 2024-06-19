#include "MACE/SimEMC/Action/ActionInitialization.h++"
#include "MACE/SimEMC/Action/DetectorConstruction.h++"
#include "MACE/SimEMC/Analysis.h++"
#include "MACE/SimEMC/PhysicsList.h++"
#include "MACE/SimEMC/RunManager.h++"

#include "Mustard/Env/BasicEnv.h++"
#include "Mustard/Utility/LiteralUnit.h++"

#include "G4TransportationParameters.hh"

#include "muc/utility"

namespace MACE::SimEMC {

using namespace Mustard::LiteralUnit::Energy;

RunManager::RunManager() :
    MPIRunManager{},
    fAnalysis{std::make_unique_for_overwrite<Analysis>()} {
    const auto verboseLevel{Mustard::Env::BasicEnv::Instance().VerboseLevel()};

    // control of the parameters for killing looping particles
    auto& transportParams{*G4TransportationParameters::Instance()};
    transportParams.SetWarningEnergy(50_eV);
    transportParams.SetImportantEnergy(50_eV);
    transportParams.SetNumberOfTrials(1000);

    const auto physicsList{new PhysicsList};
    physicsList->SetVerboseLevel(muc::to_underlying(verboseLevel));
    SetUserInitialization(physicsList);

    const auto detectorConstruction{new DetectorConstruction};
    detectorConstruction->SetCheckOverlaps(Mustard::Env::VerboseLevelReach<'I'>());
    SetUserInitialization(detectorConstruction);

    SetUserInitialization(new ActionInitialization);
}

RunManager::~RunManager() = default;

} // namespace MACE::SimEMC
