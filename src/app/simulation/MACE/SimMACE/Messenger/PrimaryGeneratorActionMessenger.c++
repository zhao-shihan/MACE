#include "MACE/SimMACE/Action/PrimaryGeneratorAction.h++"
#include "MACE/SimMACE/Messenger/PrimaryGeneratorActionMessenger.h++"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"

namespace MACE::SimMACE::inline Messenger {

PrimaryGeneratorActionMessenger::PrimaryGeneratorActionMessenger() :
    SingletonMessenger{},
    fTimeRMS{},
    fMuonsForEachG4Event{} {

    fTimeRMS = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Generator/SurfaceMuon/TimeRMS", this);
    fTimeRMS->SetGuidance("Set time width (RMS) of beam.");
    fTimeRMS->SetParameterName("time width", false);
    fTimeRMS->SetUnitCategory("Time");
    fTimeRMS->AvailableForStates(G4State_Idle);

    fMuonsForEachG4Event = std::make_unique<G4UIcmdWithAnInteger>("/MACE/Generator/SurfaceMuon/MuonsForEachG4Event", this);
    fMuonsForEachG4Event->SetGuidance("Set muons generated for each G4 event.");
    fMuonsForEachG4Event->SetParameterName("n", false);
    fMuonsForEachG4Event->AvailableForStates(G4State_Idle);
}

PrimaryGeneratorActionMessenger::~PrimaryGeneratorActionMessenger() = default;

auto PrimaryGeneratorActionMessenger::SetNewValue(G4UIcommand* command, G4String value) -> void {
    if (command == fTimeRMS.get()) {
        Deliver<PrimaryGeneratorAction>([&](auto&& r) {
            r.TimeRMS(fTimeRMS->GetNewDoubleValue(value));
        });
    } else if (command == fMuonsForEachG4Event.get()) {
        Deliver<PrimaryGeneratorAction>([&](auto&& r) {
            r.MuonsForEachG4Event(fMuonsForEachG4Event->GetNewIntValue(value));
        });
    }
}

} // namespace MACE::SimMACE::inline Messenger
