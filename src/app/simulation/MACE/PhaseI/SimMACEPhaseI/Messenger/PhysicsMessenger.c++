#include "MACE/PhaseI/SimMACEPhaseI/Messenger/PhysicsMessenger.h++"
#include "MACE/PhaseI/SimMACEPhaseI/PhysicsList.h++"

#include "G4UIcommand.hh"
#include "G4UnitsTable.hh"

namespace MACE::PhaseI::SimMACEPhaseI::inline Messenger {

PhysicsMessenger::PhysicsMessenger() :
    SingletonMessenger{},
    fUseOpticalPhysics{} {

    fUseOpticalPhysics = std::make_unique<G4UIcommand>("/MACE/Physics/UseOpticalPhysics", this);
    fUseOpticalPhysics->SetGuidance("If set then the G4OpticalPhysics will be registered in the PhysicsList.");
    fUseOpticalPhysics->AvailableForStates(G4State_PreInit);
}

PhysicsMessenger::~PhysicsMessenger() = default;

auto PhysicsMessenger::SetNewValue(G4UIcommand* command, G4String) -> void {
    if (command == fUseOpticalPhysics.get()) {
        Deliver<PhysicsList>([&](auto&& r) {
            r.UseOpticalPhysics();
        });
    }
}

} // namespace MACE::PhaseI::SimMACEPhaseI::inline Messenger
