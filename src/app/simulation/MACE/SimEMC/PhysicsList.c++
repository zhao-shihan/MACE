#include "MACE/Compatibility/std23/to_underlying.h++"
#include "MACE/Env/BasicEnv.h++"
#include "MACE/SimEMC/PhysicsList.h++"

#include "G4EmStandardPhysics_option4.hh"
#include "G4OpticalParameters.hh"
#include "G4OpticalPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"

#include <algorithm>

namespace MACE::SimEMC {

PhysicsList::PhysicsList() :
    PassiveSingleton{},
    FTFP_BERT{std::max({}, std23::to_underlying(Env::BasicEnv::Instance().VerboseLevel()))},
    fMessengerRegister{this} {
    // EMZ
    ReplacePhysics(new G4EmStandardPhysics_option4{verboseLevel});
    RegisterPhysics(new G4RadioactiveDecayPhysics(verboseLevel));
}

auto PhysicsList::UseOpticalPhysics() -> void {
    RegisterPhysics(new G4OpticalPhysics(verboseLevel));
    G4OpticalParameters::Instance()->SetBoundaryInvokeSD(true);
}

} // namespace MACE::SimEMC
