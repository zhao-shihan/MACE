#include "MACE/Detector/Description/Target.h++"
#include "MACE/SimDose/Action/ActionInitialization.h++"
#include "MACE/SimDose/Action/DetectorConstruction.h++"
#include "MACE/SimDose/Analysis.h++"
#include "MACE/SimDose/RunManager.h++"

#include "Mustard/Env/BasicEnv.h++"
#include "Mustard/Extension/Geant4X/Physics/MuonPrecisionDecayPhysics.h++"
#include "Mustard/Extension/Geant4X/Physics/MuoniumPhysics.h++"
#include "Mustard/Extension/Geant4X/Physics/MuoniumPrecisionDecayPhysics.h++"
#include "Mustard/Utility/LiteralUnit.h++"

#include "G4SpinDecayPhysics.hh"
#include "G4StepLimiterPhysics.hh"
#include "G4VModularPhysicsList.hh"

#include "muc/utility"

namespace MACE::SimDose {

using namespace Mustard::LiteralUnit::Energy;

RunManager::RunManager(Mustard::Env::CLI::Geant4ReferencePhysicsListModule<"QBBC_EMZ">& cli) :
    MPIRunManager{},
    fAnalysis{std::make_unique_for_overwrite<Analysis>()} {
    const auto verboseLevel{muc::to_underlying(Mustard::Env::BasicEnv::Instance().VerboseLevel())};

    const auto physicsList{cli.PhysicsList()};
    // Muonium physics
    physicsList->RegisterPhysics(new Mustard::Geant4X::MuoniumPhysics<Detector::Description::Target>{verboseLevel});
    // HP decay for muon and muonium
    physicsList->ReplacePhysics(new G4SpinDecayPhysics{verboseLevel});
    physicsList->RegisterPhysics(new Mustard::Geant4X::MuonPrecisionDecayPhysics{verboseLevel});
    physicsList->RegisterPhysics(new Mustard::Geant4X::MuoniumPrecisionDecayPhysics{verboseLevel});
    // Step limit
    physicsList->ReplacePhysics(new G4StepLimiterPhysics);
    SetUserInitialization(physicsList);

    const auto detectorConstruction{new DetectorConstruction};
    detectorConstruction->SetCheckOverlaps(Mustard::Env::VerboseLevelReach<'I'>());
    SetUserInitialization(detectorConstruction);

    SetUserInitialization(new ActionInitialization);
}

RunManager::~RunManager() = default;

} // namespace MACE::SimDose
