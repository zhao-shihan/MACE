#include "MACE/Simulation/Physics/MuoniumPhysics.hxx"
#include "MACE/Simulation/SimMACE/Action/PhysicsList.hxx"

#include "G4DecayPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4HadronPhysicsFTFP_BERT.hh"
#include "G4IonPhysics.hh"
#include "G4NeutronTrackingCut.hh"
#include "G4ProductionCuts.hh"
#include "G4RegionStore.hh"
#include "G4StoppingPhysics.hh"

namespace MACE::Simulation::SimMACE::Action {

using namespace MACE::Simulation::Physics;

PhysicsList::PhysicsList() :
    G4VModularPhysicsList() {
    constexpr G4int verbose = 0;
    SetVerboseLevel(verbose);
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

} // namespace MACE::Simulation::SimMACE::Action
