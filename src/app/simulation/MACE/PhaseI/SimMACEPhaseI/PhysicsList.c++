#include "MACE/Env/BasicEnv.h++"
#include "MACE/PhaseI/SimMACEPhaseI/PhysicsList.h++"

#include "G4OpticalParameters.hh"
#include "G4OpticalPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"

#include "muc/utility"

#include <algorithm>

namespace MACE::PhaseI::SimMACEPhaseI {

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

} // namespace MACE::PhaseI::SimMACEPhaseI
