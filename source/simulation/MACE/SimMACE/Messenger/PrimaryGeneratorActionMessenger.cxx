#include "MACE/SimMACE/Action/PrimaryGeneratorAction.hxx"
#include "MACE/SimMACE/Messenger/PrimaryGeneratorActionMessenger.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UnitsTable.hh"

namespace MACE::SimMACE::Messenger {

using namespace MACE::Utility::LiteralUnit::Frequency;

PrimaryGeneratorActionMessenger::PrimaryGeneratorActionMessenger() :
    Singleton(),
    G4UImessenger(),
    fPrimaryGeneratorAction(nullptr),
    fSetFlux(),
    fSetRepetitionRate(),
    fSetTimeWidthRMS(),
    fSetMuonsForEachG4Event() {

    // Introduce some useful units.
    // per unit time (for beam flux)
    new G4UnitDefinition("second-1", "s-1", "Time-1", 1_s_1);
    new G4UnitDefinition("millisecond-1", "ms-1", "Time-1", 1_ms_1);
    new G4UnitDefinition("microsecond-1", "us-1", "Time-1", 1_us_1);

    fSetFlux = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Generator/SurfaceMuon/SetFlux", this);
    fSetFlux->SetGuidance("Set muon flux.");
    fSetFlux->SetParameterName("flux", false);
    fSetFlux->SetUnitCategory("Time-1");
    fSetFlux->AvailableForStates(G4State_Idle);

    fSetRepetitionRate = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Generator/SurfaceMuon/SetRepetitionRate", this);
    fSetRepetitionRate->SetGuidance("Set repetition rate of beam.");
    fSetRepetitionRate->SetParameterName("repetition rate", false);
    fSetRepetitionRate->SetUnitCategory("Frequency");
    fSetRepetitionRate->AvailableForStates(G4State_Idle);

    fSetTimeWidthRMS = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Generator/SurfaceMuon/SetTimeWidthRMS", this);
    fSetTimeWidthRMS->SetGuidance("Set time width (RMS) of beam.");
    fSetTimeWidthRMS->SetParameterName("time width", false);
    fSetTimeWidthRMS->SetUnitCategory("Time");
    fSetTimeWidthRMS->AvailableForStates(G4State_Idle);

    fSetMuonsForEachG4Event = std::make_unique<G4UIcmdWithAnInteger>("/MACE/Generator/SurfaceMuon/SetMuonsForEachG4Event", this);
    fSetMuonsForEachG4Event->SetGuidance("Set muons generated for each G4 event. Beam properties won't be affected unless the value is greater than muons per repetition. In common case, a few hundred to thousand is OK.");
    fSetMuonsForEachG4Event->SetParameterName("n", false);
    fSetMuonsForEachG4Event->AvailableForStates(G4State_Idle);
}

PrimaryGeneratorActionMessenger::~PrimaryGeneratorActionMessenger() = default;

void PrimaryGeneratorActionMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    if (command == fSetFlux.get()) {
        fPrimaryGeneratorAction->SetFlux(fSetFlux->GetNewDoubleValue(value));
    } else if (command == fSetRepetitionRate.get()) {
        fPrimaryGeneratorAction->SetRepetitionRate(fSetRepetitionRate->GetNewDoubleValue(value));
    } else if (command == fSetTimeWidthRMS.get()) {
        fPrimaryGeneratorAction->SetTimeWidthRMS(fSetTimeWidthRMS->GetNewDoubleValue(value));
    } else if (command == fSetMuonsForEachG4Event.get()) {
        fPrimaryGeneratorAction->SetMuonsForEachG4Event(fSetMuonsForEachG4Event->GetNewIntValue(value));
    }
}

} // namespace MACE::SimMACE::Messenger
