#include "MACE/SimTarget/Action/PrimaryGeneratorAction.h++"
#include "MACE/SimTarget/Messenger/PrimaryGeneratorActionMessenger.h++"

#include "G4UIcmdWithAnInteger.hh"

namespace MACE::SimTarget::inline Messenger {

PrimaryGeneratorActionMessenger::PrimaryGeneratorActionMessenger() :
    Singleton(),
    G4UImessenger(),
    fPrimaryGeneratorAction(nullptr),
    fMuonsForEachG4Event() {

    fMuonsForEachG4Event = std::make_unique<G4UIcmdWithAnInteger>("/MACE/Generator/SurfaceMuon/MuonsForEachG4Event", this);
    fMuonsForEachG4Event->SetGuidance("Set muons generated for each G4 event.");
    fMuonsForEachG4Event->SetParameterName("n", false);
    fMuonsForEachG4Event->AvailableForStates(G4State_Idle);
}

PrimaryGeneratorActionMessenger::~PrimaryGeneratorActionMessenger() = default;

auto PrimaryGeneratorActionMessenger::SetNewValue(G4UIcommand* command, G4String value) -> void {
    if (command == fMuonsForEachG4Event.get()) {
        fPrimaryGeneratorAction->MuonsForEachG4Event(fMuonsForEachG4Event->GetNewIntValue(value));
    }
}

} // namespace MACE::SimTarget::inline Messenger
