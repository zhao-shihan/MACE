#include "MACE/Compatibility/std2b/to_underlying.h++"
#include "MACE/Detector/Description/Target.h++"
#include "MACE/Env/BasicEnv.h++"
#include "MACE/Simulation/Physics/MuoniumPhysics.h++"
#include "MACE/SimMACE/PhysicsList.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4DecayPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4HadronPhysicsFTFP_BERT.hh"
#include "G4IonPhysics.hh"
#include "G4NeutronTrackingCut.hh"
#include "G4StoppingPhysics.hh"

namespace MACE::SimMACE {

using namespace MACE::LiteralUnit::Length;

PhysicsList::PhysicsList() :
    PassiveSingleton(),
    G4VModularPhysicsList() {

    verboseLevel = std2b::to_underlying(Env::BasicEnv::Instance().GetVerboseLevel());
    defaultCutValue = 700_um;

    // EM Physics
    RegisterPhysics(new G4EmStandardPhysics_option4(verboseLevel));

    // Synchroton Radiation & GN Physics
    RegisterPhysics(new G4EmExtraPhysics(verboseLevel));

    // Decays
    RegisterPhysics(new G4DecayPhysics(verboseLevel));

    // Hadron Elastic scattering
    RegisterPhysics(new G4HadronElasticPhysics(verboseLevel));

    // Hadron Physics
    RegisterPhysics(new G4HadronPhysicsFTFP_BERT(verboseLevel));

    // Stopping Physics
    RegisterPhysics(new G4StoppingPhysics(verboseLevel));

    // Ion Physics
    RegisterPhysics(new G4IonPhysics(verboseLevel));

    // Neutron tracking cut
    RegisterPhysics(new G4NeutronTrackingCut(verboseLevel));

    // Muonium physics
    RegisterPhysics(new Physics::MuoniumPhysics<Detector::Description::Target>(verboseLevel));
}

} // namespace MACE::SimMACE
