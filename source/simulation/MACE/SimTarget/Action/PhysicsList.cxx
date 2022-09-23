#include "MACE/Compatibility/std2b/to_underlying.hxx"
#include "MACE/Environment/BasicEnvironment.hxx"
#include "MACE/Geant4X/Physics/MuoniumPhysics.hxx"
#include "MACE/SimTarget/Action/PhysicsList.hxx"

#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics_option4.hh"

namespace MACE::SimTarget::Action {

namespace std2b = Compatibility::std2b;
using namespace MACE::Geant4X::Physics;

PhysicsList::PhysicsList() :
    FreeSingleton(),
    G4VModularPhysicsList() {
    verboseLevel = std2b::to_underlying(Environment::BasicEnvironment::Instance().GetVerboseLevel());
    RegisterPhysics(new G4EmStandardPhysics_option4(verboseLevel));
    RegisterPhysics(new G4DecayPhysics(verboseLevel));
    RegisterPhysics(new MuoniumPhysics(verboseLevel));
}

} // namespace MACE::SimTarget::Action
