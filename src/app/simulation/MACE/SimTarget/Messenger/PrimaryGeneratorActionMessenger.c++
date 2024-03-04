#include "MACE/SimTarget/Action/PrimaryGeneratorAction.h++"
#include "MACE/SimTarget/Messenger/PrimaryGeneratorActionMessenger.h++"

#include "G4UIcmdWithAnInteger.hh"

namespace MACE::SimTarget::inline Messenger {

PrimaryGeneratorActionMessenger::PrimaryGeneratorActionMessenger() :
    SingletonMessenger{},
    fPrimariesForEachG4Event{} {

    fPrimariesForEachG4Event = std::make_unique<G4UIcmdWithAnInteger>("/MACE/Generator/GPS/PrimariesForEachG4Event", this);
    fPrimariesForEachG4Event->SetGuidance("Set muons generated for each G4 event.");
    fPrimariesForEachG4Event->SetParameterName("n", false);
    fPrimariesForEachG4Event->AvailableForStates(G4State_Idle);
}

PrimaryGeneratorActionMessenger::~PrimaryGeneratorActionMessenger() = default;

auto PrimaryGeneratorActionMessenger::SetNewValue(G4UIcommand* command, G4String value) -> void {
    if (command == fPrimariesForEachG4Event.get()) {
        Deliver<PrimaryGeneratorAction>([&](auto&& r) {
            r.PrimariesForEachG4Event(fPrimariesForEachG4Event->GetNewIntValue(value));
        });
    }
}

} // namespace MACE::SimTarget::inline Messenger
