#include "MACE/Detector/Description/Target.h++"
#include "MACE/Simulation/Physics/StandardPhysicsList.h++"

#include "Mustard/Env/BasicEnv.h++"
#include "Mustard/Extension/Geant4X/Physics/MuonPrecisionDecayPhysics.h++"
#include "Mustard/Extension/Geant4X/Physics/MuoniumPhysics.h++"
#include "Mustard/Extension/Geant4X/Physics/MuoniumPrecisionDecayPhysics.h++"
#include "Mustard/Extension/Geant4X/Physics/MuoniumTwoBodyDecayPhysics.h++"
#include "Mustard/Utility/LiteralUnit.h++"

#include "G4EmParameters.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4MscStepLimitType.hh"
#include "G4SpinDecayPhysics.hh"

#include "muc/utility"

#include <algorithm>

namespace MACE::inline Simulation::inline Physics {

StandardPhysicsListBase::StandardPhysicsListBase() :
    QBBC{std::max({}, muc::to_underlying(Mustard::Env::BasicEnv::Instance().VerboseLevel()))} {
    // EMZ
    ReplacePhysics(new G4EmStandardPhysics_option4{verboseLevel});
    // Muonium physics
    RegisterPhysics(new Mustard::Geant4X::MuoniumPhysics<Detector::Description::Target>{verboseLevel});
    // HP decay for muon and muonium
    ReplacePhysics(new G4SpinDecayPhysics{verboseLevel});
    RegisterPhysics(new Mustard::Geant4X::MuonPrecisionDecayPhysics{verboseLevel});
    RegisterPhysics(new Mustard::Geant4X::MuoniumPrecisionDecayPhysics{verboseLevel});

    // Set EM parameters
    using namespace Mustard::LiteralUnit::Energy;
    auto& emParameter{*G4EmParameters::Instance()};
    emParameter.SetLowestElectronEnergy(0.1_eV);
    emParameter.SetLowestMuHadEnergy(0.1_eV);
    emParameter.SetLowestTripletEnergy(0.1_eV);
    emParameter.SetMinEnergy(0.1_eV);
    emParameter.SetMscMuHadStepLimitType(fUseSafetyPlus);
    emParameter.SetMscPositronCorrection(true);
}

} // namespace MACE::inline Simulation::inline Physics
