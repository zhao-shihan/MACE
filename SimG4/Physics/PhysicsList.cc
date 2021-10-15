#include "G4EmLivermorePhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4HadronPhysicsFTFP_BERT.hh"
#include "G4StoppingPhysics.hh"
#include "G4IonPhysics.hh"
#include "G4NeutronTrackingCut.hh"
#include "G4DecayPhysics.hh"

#include "SimG4/Physics/PhysicsList.hh"
#include "SimG4/Physics/MuoniumPhysics.hh"

using namespace MACE::SimG4::Physics;

PhysicsList::PhysicsList(G4int verbose) :
    G4VModularPhysicsList(),
    fVerbose(verbose) {
    RegisterPhysics(new G4EmLivermorePhysics(verbose));
    RegisterPhysics(new G4EmExtraPhysics(verbose));
    RegisterPhysics(new G4DecayPhysics(verbose));
    RegisterPhysics(new G4HadronElasticPhysics(verbose));
    RegisterPhysics(new G4HadronPhysicsFTFP_BERT(verbose));
    RegisterPhysics(new G4StoppingPhysics(verbose));
    RegisterPhysics(new G4IonPhysics(verbose));
    RegisterPhysics(new G4NeutronTrackingCut(verbose));
    RegisterPhysics(new MuoniumPhysics(verbose));
}
