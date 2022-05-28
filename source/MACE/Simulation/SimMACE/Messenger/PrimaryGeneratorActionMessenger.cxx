#include "MACE/Simulation/SimMACE/Action/PrimaryGeneratorAction.hxx"
#include "MACE/Simulation/SimMACE/Messenger/PrimaryGeneratorActionMessenger.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include "G4UnitsTable.hh"

namespace MACE::Simulation::SimMACE::Messenger {

using namespace MACE::Utility::LiteralUnit::Frequency;

PrimaryGeneratorActionMessenger& PrimaryGeneratorActionMessenger::Instance() {
    static PrimaryGeneratorActionMessenger instance;
    return instance;
}

PrimaryGeneratorActionMessenger::PrimaryGeneratorActionMessenger() :
    G4UImessenger(),
    fSetFlux("/MACE/Generator/SurfaceMuon/SetFlux", this),
    fSetRepetitionRate("/MACE/Generator/SurfaceMuon/SetRepetitionRate", this),
    fSetTimeWidthRMS("/MACE/Generator/SurfaceMuon/SetTimeWidthRMS", this),
    fSetMuonsForEachG4Event("/MACE/Generator/SurfaceMuon/SetMuonsForEachG4Event", this) {

    // Introduce some useful units.
    // per unit time (for beam flux)
    new G4UnitDefinition("second-1", "s-1", "Time-1", 1_s_1);
    new G4UnitDefinition("millisecond-1", "ms-1", "Time-1", 1_ms_1);
    new G4UnitDefinition("microsecond-1", "us-1", "Time-1", 1_us_1);

    fSetFlux.SetGuidance("Set muon flux.");
    fSetFlux.SetParameterName("flux", false);
    fSetFlux.SetUnitCategory("Time-1");
    fSetFlux.AvailableForStates(G4State_Idle);

    fSetRepetitionRate.SetGuidance("Set repetition rate of beam.");
    fSetRepetitionRate.SetParameterName("repetition rate", false);
    fSetRepetitionRate.SetUnitCategory("Frequency");
    fSetRepetitionRate.AvailableForStates(G4State_Idle);

    fSetTimeWidthRMS.SetGuidance("Set time width (RMS) of beam.");
    fSetTimeWidthRMS.SetParameterName("time width", false);
    fSetTimeWidthRMS.SetUnitCategory("Time");
    fSetTimeWidthRMS.AvailableForStates(G4State_Idle);

    fSetMuonsForEachG4Event.SetGuidance("Set muons generated for each G4 event. Beam properties won't be affected unless the value is greater than muons per repetition. In common case, a few hundred to thousand is OK.");
    fSetMuonsForEachG4Event.SetParameterName("n", false);
    fSetMuonsForEachG4Event.AvailableForStates(G4State_Idle);
}

void PrimaryGeneratorActionMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    if (command == std::addressof(fSetFlux)) {
        fPrimaryGeneratorAction->SetFlux(fSetFlux.GetNewDoubleValue(value));
    } else if (command == std::addressof(fSetRepetitionRate)) {
        fPrimaryGeneratorAction->SetRepetitionRate(fSetRepetitionRate.GetNewDoubleValue(value));
    } else if (command == std::addressof(fSetTimeWidthRMS)) {
        fPrimaryGeneratorAction->SetTimeWidthRMS(fSetTimeWidthRMS.GetNewDoubleValue(value));
    } else if (command == std::addressof(fSetMuonsForEachG4Event)) {
        fPrimaryGeneratorAction->SetMuonsForEachG4Event(fSetMuonsForEachG4Event.GetNewIntValue(value));
    }
}

} // namespace MACE::Simulation::SimMACE::Messenger
