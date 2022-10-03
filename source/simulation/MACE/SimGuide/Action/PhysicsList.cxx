#include "MACE/Compatibility/std2b/to_underlying.hxx"
#include "MACE/Env/BasicEnv.hxx"
#include "MACE/SimGuide/Action/PhysicsList.hxx"

#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics_option4.hh"

namespace MACE::SimGuide::Action {

namespace std2b = Compatibility::std2b;
using namespace MACE::Geant4X::Physics;

PhysicsList::PhysicsList() :
    FreeSingleton(),
    G4VModularPhysicsList() {
    verboseLevel = std2b::to_underlying(Env::BasicEnv::Instance().GetVerboseLevel());
    RegisterPhysics(new G4EmStandardPhysics_option4(verboseLevel));
    RegisterPhysics(new G4DecayPhysics(verboseLevel));
}

} // namespace MACE::SimGuide::Action
