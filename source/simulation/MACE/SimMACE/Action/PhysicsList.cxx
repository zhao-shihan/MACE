#include "MACE/Compatibility/std2b/to_underlying.hxx"
#include "MACE/Env/BasicEnv.hxx"
#include "MACE/Extension/Geant4X/Physics/MuoniumPhysics.hxx"
#include "MACE/Detector/Description/Target.hxx"
#include "MACE/SimMACE/Action/PhysicsList.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include "G4DecayPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4HadronElasticPhysicsXS.hh"
#include "G4HadronInelasticQBBC.hh"
#include "G4IonElasticPhysics.hh"
#include "G4IonPhysicsXS.hh"
#include "G4NeutronTrackingCut.hh"
#include "G4StoppingPhysics.hh"

namespace MACE::SimMACE::Action {

using namespace MACE::Geant4X::Physics;
using namespace MACE::LiteralUnit::Length;

PhysicsList::PhysicsList() :
    G4VModularPhysicsList() {

    verboseLevel = std2b::to_underlying(Env::BasicEnv::Instance().GetVerboseLevel());
    defaultCutValue = 700_um;

    // EM Physics
    RegisterPhysics(new G4EmStandardPhysics_option4(verboseLevel));

    // Synchroton Radiation & Gamma-Nuclear Physics
    RegisterPhysics(new G4EmExtraPhysics(verboseLevel));

    // Decays
    RegisterPhysics(new G4DecayPhysics(verboseLevel));

    // Hadron Physics
    RegisterPhysics(new G4HadronElasticPhysicsXS(verboseLevel));
    RegisterPhysics(new G4StoppingPhysics(verboseLevel));
    RegisterPhysics(new G4IonPhysicsXS(verboseLevel));
    RegisterPhysics(new G4IonElasticPhysics(verboseLevel));
    RegisterPhysics(new G4HadronInelasticQBBC(verboseLevel));

    // Neutron tracking cut
    RegisterPhysics(new G4NeutronTrackingCut(verboseLevel));

    // Muonium formation & transport
    RegisterPhysics(new MuoniumPhysics<Detector::Description::Target>(verboseLevel));
}

} // namespace MACE::SimMACE::Action
