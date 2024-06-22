#include "MACE/SimEMC/PhysicsList.h++"

#include "Mustard/Env/BasicEnv.h++"

#include "G4EmParameters.hh"
#include "G4OpticalParameters.hh"
#include "G4OpticalPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"

#include "muc/utility"

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
