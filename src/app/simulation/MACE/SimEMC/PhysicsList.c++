#include "MACE/Compatibility/std23/to_underlying.h++"
#include "MACE/Env/BasicEnv.h++"
#include "MACE/SimEMC/PhysicsList.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4DecayPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4OpticalPhysics.hh"

namespace MACE::SimEMC {

using namespace MACE::LiteralUnit::Length;

PhysicsList::PhysicsList() :
    PassiveSingleton(),
    G4VModularPhysicsList() {

    verboseLevel = std23::to_underlying(Env::BasicEnv::Instance().GetVerboseLevel());
    defaultCutValue = 700_um;

    // EM Physics
    RegisterPhysics(new G4EmStandardPhysics_option4(verboseLevel));

    // Synchroton Radiation & GN Physics
    RegisterPhysics(new G4EmExtraPhysics(verboseLevel));

    // Decays
    RegisterPhysics(new G4DecayPhysics(verboseLevel));

    // Optical
    RegisterPhysics(new G4OpticalPhysics(verboseLevel));
    G4OpticalParameters::Instance()->SetBoundaryInvokeSD(true);
}

} // namespace MACE::SimEMC
