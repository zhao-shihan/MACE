#include "MACE/SimTarget/Action/PrimaryGeneratorAction.hxx"
#include "MACE/SimTarget/Messenger/PrimaryGeneratorActionMessenger.hxx"

#include "G4UIcmdWithAnInteger.hh"
#include "G4UIdirectory.hh"

namespace MACE::SimTarget::Messenger {

PrimaryGeneratorActionMessenger::PrimaryGeneratorActionMessenger() :
    Singleton(),
    G4UImessenger(),
    fPrimaryGeneratorAction(nullptr),
    fDirectory(),
    fSetMuonsForEachG4Event() {

    fDirectory = std::make_unique<G4UIdirectory>("/MACE/Generator/");

    fSetMuonsForEachG4Event = std::make_unique<G4UIcmdWithAnInteger>("/MACE/Generator/SurfaceMuon/SetMuonsForEachG4Event", this);
    fSetMuonsForEachG4Event->SetGuidance("Set muons generated for each G4 event.");
    fSetMuonsForEachG4Event->SetParameterName("n", false);
    fSetMuonsForEachG4Event->AvailableForStates(G4State_Idle);
}

PrimaryGeneratorActionMessenger::~PrimaryGeneratorActionMessenger() = default;

void PrimaryGeneratorActionMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    if (command == fSetMuonsForEachG4Event.get()) {
        fPrimaryGeneratorAction->SetMuonsForEachG4Event(fSetMuonsForEachG4Event->GetNewIntValue(value));
    }
}

} // namespace MACE::SimTarget::Messenger
