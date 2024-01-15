#include "MACE/Compatibility/std23/to_underlying.h++"
#include "MACE/Env/BasicEnv.h++"
#include "MACE/SimGuide/Action/PhysicsList.h++"

#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics_option4.hh"

namespace MACE::SimGuide::inline Action {

using namespace MACE::Geant4X::Physics;

PhysicsList::PhysicsList() :
    PassiveSingleton(),
    G4VModularPhysicsList() {
    verboseLevel = std23::to_underlying(Env::BasicEnv::Instance().GetVerboseLevel());
    RegisterPhysics(new G4EmStandardPhysics_option4(verboseLevel));
    RegisterPhysics(new G4DecayPhysics(verboseLevel));
}

} // namespace MACE::SimGuide::inline Action
