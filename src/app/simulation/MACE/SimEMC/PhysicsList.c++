#include "MACE/Compatibility/std23/to_underlying.h++"
#include "MACE/Env/BasicEnv.h++"
#include "MACE/SimEMC/PhysicsList.h++"

#include "G4OpticalParameters.hh"
#include "G4OpticalPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"

#include <algorithm>

namespace MACE::SimEMC {

PhysicsList::PhysicsList() :
    PassiveSingleton<PhysicsList>{},
    StandardPhysicsListBase{},
    fMessengerRegister{this} {
    RegisterPhysics(new G4RadioactiveDecayPhysics{verboseLevel});
}

auto PhysicsList::UseOpticalPhysics() -> void {
    RegisterPhysics(new G4OpticalPhysics{verboseLevel});
    G4OpticalParameters::Instance()->SetBoundaryInvokeSD(true);
}

} // namespace MACE::SimEMC
