#include "MACE/SimulationG4/Physics/MuoniumPhysics.hxx"
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

using namespace MACE::SimulationG4::Physics;

PhysicsList::PhysicsList() :
    G4VModularPhysicsList() {
    constexpr G4int defaultVerbose = 0;
    SetVerboseLevel(defaultVerbose);
    RegisterPhysics(new G4EmStandardPhysics_option4(defaultVerbose));
    RegisterPhysics(new G4EmExtraPhysics(defaultVerbose));
    RegisterPhysics(new G4DecayPhysics(defaultVerbose));
    RegisterPhysics(new G4HadronElasticPhysics(defaultVerbose));
    RegisterPhysics(new G4HadronPhysicsFTFP_BERT(defaultVerbose));
    RegisterPhysics(new G4StoppingPhysics(defaultVerbose));
    RegisterPhysics(new G4IonPhysics(defaultVerbose));
    RegisterPhysics(new G4NeutronTrackingCut(defaultVerbose));
    RegisterPhysics(new MuoniumPhysics(defaultVerbose));
}

} // namespace MACE::SimMACE::Action
