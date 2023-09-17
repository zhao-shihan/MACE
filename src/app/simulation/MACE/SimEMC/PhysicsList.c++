#include "MACE/Compatibility/std2b/to_underlying.h++"
#include "MACE/Env/BasicEnv.h++"
#include "MACE/SimEMC/PhysicsList.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4DecayPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4EmStandardPhysics_option4.hh"

namespace MACE::SimEMC {

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
}

} // namespace MACE::SimEMC
