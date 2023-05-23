#include "MACE/Compatibility/std2b/to_underlying.hxx"
#include "MACE/Detector/Description/Target.hxx"
#include "MACE/Env/BasicEnv.hxx"
#include "MACE/Extension/Geant4X/Physics/MuoniumPhysics.hxx"
#include "MACE/SimMACE/PhysicsList.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include "G4DecayPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4HadronPhysicsFTFP_BERT.hh"
#include "G4IonPhysics.hh"
#include "G4NeutronTrackingCut.hh"
#include "G4StoppingPhysics.hh"

namespace MACE::SimMACE {

using namespace MACE::Geant4X::Physics;
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
    RegisterPhysics(new MuoniumPhysics<Detector::Description::Target>(verboseLevel));
}

} // namespace MACE::SimMACE
