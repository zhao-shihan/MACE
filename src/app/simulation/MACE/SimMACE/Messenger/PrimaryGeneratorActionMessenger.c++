#include "MACE/SimMACE/Action/PrimaryGeneratorAction.h++"
#include "MACE/SimMACE/Messenger/PrimaryGeneratorActionMessenger.h++"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"

namespace MACE::SimMACE::inline Messenger {

PrimaryGeneratorActionMessenger::PrimaryGeneratorActionMessenger() :
    SingletonMessenger{},
    fPulseWidth{},
    fPrimariesForEachG4Event{} {

    fPulseWidth = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Generator/GPS/PulseWidth", this);
    fPulseWidth->SetGuidance("Set pulse width of beam.");
    fPulseWidth->SetParameterName("pulse width", false);
    fPulseWidth->SetUnitCategory("T");
    fPulseWidth->SetRange("T >= 0");
    fPulseWidth->AvailableForStates(G4State_Idle);

    fPrimariesForEachG4Event = std::make_unique<G4UIcmdWithAnInteger>("/MACE/Generator/GPS/PrimariesForEachG4Event", this);
    fPrimariesForEachG4Event->SetGuidance("Set muons generated for each G4 event.");
    fPrimariesForEachG4Event->SetParameterName("N", false);
    fPrimariesForEachG4Event->SetRange("N >= 1");
    fPrimariesForEachG4Event->AvailableForStates(G4State_Idle);
}

PrimaryGeneratorActionMessenger::~PrimaryGeneratorActionMessenger() = default;

auto PrimaryGeneratorActionMessenger::SetNewValue(G4UIcommand* command, G4String value) -> void {
    if (command == fPulseWidth.get()) {
        Deliver<PrimaryGeneratorAction>([&](auto&& r) {
            r.PulseWidth(fPulseWidth->GetNewDoubleValue(value));
        });
    } else if (command == fPrimariesForEachG4Event.get()) {
        Deliver<PrimaryGeneratorAction>([&](auto&& r) {
            r.PrimariesForEachG4Event(fPrimariesForEachG4Event->GetNewIntValue(value));
        });
    }
}

} // namespace MACE::SimMACE::inline Messenger
