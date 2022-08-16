#include "MACE/Compatibility/Std2b/ToUnderlying.hxx"
#include "MACE/Environment/BasicEnvironment.hxx"
#include "MACE/Geant4X/Physics/MuoniumPhysics.hxx"
#include "MACE/SimMACE/Action/PhysicsList.hxx"

#include "G4DecayPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4HadronPhysicsFTFP_BERT.hh"
#include "G4IonPhysics.hh"
#include "G4NeutronTrackingCut.hh"
#include "G4StoppingPhysics.hh"

namespace MACE::SimMACE::Action {

namespace Std2b = Compatibility::Std2b;
using namespace MACE::Geant4X::Physics;

PhysicsList::PhysicsList() :
    G4VModularPhysicsList() {
    verboseLevel = Std2b::ToUnderlying(Environment::BasicEnvironment::Instance().GetVerboseLevel());
    RegisterPhysics(new G4EmStandardPhysics_option4(verboseLevel));
    RegisterPhysics(new G4EmExtraPhysics(verboseLevel));
    RegisterPhysics(new G4DecayPhysics(verboseLevel));
    RegisterPhysics(new G4HadronElasticPhysics(verboseLevel));
    RegisterPhysics(new G4HadronPhysicsFTFP_BERT(verboseLevel));
    RegisterPhysics(new G4StoppingPhysics(verboseLevel));
    RegisterPhysics(new G4IonPhysics(verboseLevel));
    RegisterPhysics(new G4NeutronTrackingCut(verboseLevel));
    RegisterPhysics(new MuoniumPhysics(verboseLevel));
}

} // namespace MACE::SimMACE::Action
