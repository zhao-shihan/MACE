#include "MACE/Simulation/SimTarget/Action/PrimaryGeneratorAction.hxx"
#include "MACE/Simulation/SimTarget/Messenger/PrimaryGeneratorActionMessenger.hxx"

#include "G4SystemOfUnits.hh"
#include "G4UIdirectory.hh"
#include "G4UnitsTable.hh"

namespace MACE::Simulation::SimTarget::Messenger {

PrimaryGeneratorActionMessenger& PrimaryGeneratorActionMessenger::Instance() {
    static PrimaryGeneratorActionMessenger instance;
    return instance;
}

PrimaryGeneratorActionMessenger::PrimaryGeneratorActionMessenger() :
    G4UImessenger(),
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

} // namespace MACE::Simulation::SimTarget::Messenger
