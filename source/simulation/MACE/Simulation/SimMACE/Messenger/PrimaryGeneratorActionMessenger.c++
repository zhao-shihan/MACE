#include "MACE/Simulation/SimMACE/Action/PrimaryGeneratorAction.h++"
#include "MACE/Simulation/SimMACE/Messenger/PrimaryGeneratorActionMessenger.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UnitsTable.hh"

namespace MACE::inline Simulation::SimMACE::inline Messenger {

using namespace MACE::LiteralUnit::Frequency;

PrimaryGeneratorActionMessenger::PrimaryGeneratorActionMessenger() :
    Singleton(),
    G4UImessenger(),
    fPrimaryGeneratorAction(nullptr),
    fTimeRMS(),
    fMuonsForEachG4Event() {

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

void PrimaryGeneratorActionMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    if (command == fTimeRMS.get()) {
        fPrimaryGeneratorAction->TimeRMS(fTimeRMS->GetNewDoubleValue(value));
    } else if (command == fMuonsForEachG4Event.get()) {
        fPrimaryGeneratorAction->MuonsForEachG4Event(fMuonsForEachG4Event->GetNewIntValue(value));
    }
}

} // namespace MACE::inline Simulation::SimMACE::inline Messenger
