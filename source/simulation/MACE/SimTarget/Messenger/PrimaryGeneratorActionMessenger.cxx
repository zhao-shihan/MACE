#include "MACE/SimTarget/Action/PrimaryGeneratorAction.hxx"
#include "MACE/SimTarget/Messenger/PrimaryGeneratorActionMessenger.hxx"

namespace MACE::SimTarget::Messenger {

PrimaryGeneratorActionMessenger::PrimaryGeneratorActionMessenger() :
    Singleton<PrimaryGeneratorActionMessenger>(),
    G4UImessenger(),
    fPrimaryGeneratorAction(nullptr),
    fSetMuonsForEachG4Event("/MACE/Generator/SurfaceMuon/SetMuonsForEachG4Event", this) {

    fSetMuonsForEachG4Event.SetGuidance("Set muons generated for each G4 event.");
    fSetMuonsForEachG4Event.SetParameterName("n", false);
    fSetMuonsForEachG4Event.AvailableForStates(G4State_Idle);
}

void PrimaryGeneratorActionMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    if (command == std::addressof(fSetMuonsForEachG4Event)) {
        fPrimaryGeneratorAction->SetMuonsForEachG4Event(fSetMuonsForEachG4Event.GetNewIntValue(value));
    }
}

} // namespace MACE::SimTarget::Messenger
