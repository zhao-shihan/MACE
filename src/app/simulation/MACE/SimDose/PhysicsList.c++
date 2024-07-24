#include "MACE/Detector/Description/Target.h++"
#include "MACE/SimDose/PhysicsList.h++"

#include "Mustard/Env/BasicEnv.h++"
#include "Mustard/Extension/Geant4X/Physics/MuonPrecisionDecayPhysics.h++"
#include "Mustard/Extension/Geant4X/Physics/MuoniumPhysics.h++"
#include "Mustard/Extension/Geant4X/Physics/MuoniumPrecisionDecayPhysics.h++"
#include "Mustard/Extension/Geant4X/Physics/MuoniumTwoBodyDecayPhysics.h++"

#include "G4EmStandardPhysics_option4.hh"
#include "G4SpinDecayPhysics.hh"
#include "G4StepLimiterPhysics.hh"

#include "muc/utility"

#include <algorithm>

namespace MACE::SimDose {

PhysicsList::PhysicsList() :
    Shielding{std::max({}, muc::to_underlying(Mustard::Env::BasicEnv::Instance().VerboseLevel()))} {
    // EMZ
    ReplacePhysics(new G4EmStandardPhysics_option4{verboseLevel});
    // Muonium physics
    RegisterPhysics(new Mustard::Geant4X::MuoniumPhysics<Detector::Description::Target>{verboseLevel});
    // HP decay for muon and muonium
    ReplacePhysics(new G4SpinDecayPhysics{verboseLevel});
    RegisterPhysics(new Mustard::Geant4X::MuonPrecisionDecayPhysics{verboseLevel});
    RegisterPhysics(new Mustard::Geant4X::MuoniumPrecisionDecayPhysics{verboseLevel});
    // Step limit
    RegisterPhysics(new G4StepLimiterPhysics);
}

} // namespace MACE::SimDose
