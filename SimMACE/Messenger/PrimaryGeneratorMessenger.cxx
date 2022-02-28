#include "G4UIdirectory.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "SimMACE/Messenger/PrimaryGeneratorMessenger.hxx"
#include "SimMACE/RunManager.hxx"
#include "SimMACE/Action/PrimaryGeneratorAction.hxx"

using namespace MACE::SimMACE::Messenger;

PrimaryGeneratorMessenger& PrimaryGeneratorMessenger::Instance() {
    static PrimaryGeneratorMessenger instance;
    return instance;
}

PrimaryGeneratorMessenger::PrimaryGeneratorMessenger() :
    G4UImessenger(),
    fDirectory("/MACE/PrimaryGenerator/"),
    fSetFlux("/MACE/PrimaryGenerator/SetFlux", this),
    fSetRepetitionRate("/MACE/PrimaryGenerator/SetRepetitionRate", this),
    fSetTimeWidthRMS("/MACE/PrimaryGenerator/SetTimeWidthRMS", this),
    fSetEnergy("/MACE/PrimaryGenerator/SetEnergy", this),
    fSetEnergySpreadRMS("/MACE/PrimaryGenerator/SetEnergySpreadRMS", this),
    fSetBeamProfileRMS("/MACE/PrimaryGenerator/SetBeamProfileRMS", this),
    fSetMuonsPerG4Event("/MACE/PrimaryGenerator/SetMuonsPerG4Event", this) {

    // Introduce some useful units.
    // per second (for beam flux)
    new G4UnitDefinition("second-1", "s-1", "Time-1", 1 / second);
    new G4UnitDefinition("millisecond-1", "ms-1", "Time-1", 1 / millisecond);
    new G4UnitDefinition("microsecond-1", "us-1", "Time-1", 1 / microsecond);

    fDirectory.SetGuidance("MACE muon beam.");

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

    fSetEnergy.SetGuidance("Set mean beam kinetic energy.");
    fSetEnergy.SetParameterName("energy", false);
    fSetEnergy.SetUnitCategory("Energy");
    fSetEnergy.AvailableForStates(G4State_Idle);

    fSetEnergySpreadRMS.SetGuidance("Set beam kinetic energy spread (RMS).");
    fSetEnergySpreadRMS.SetParameterName("energy spread", false);
    fSetEnergySpreadRMS.SetUnitCategory("Energy");
    fSetEnergySpreadRMS.AvailableForStates(G4State_Idle);

    fSetBeamProfileRMS.SetGuidance("Set beam profile width (RMS).");
    fSetBeamProfileRMS.SetParameterName("profile width", false);
    fSetBeamProfileRMS.SetUnitCategory("Length");
    fSetBeamProfileRMS.AvailableForStates(G4State_Idle);

    fSetMuonsPerG4Event.SetGuidance("Set muons generated for each G4 event. Beam properties are not affected if the value is proper.");
    fSetMuonsPerG4Event.SetParameterName("n", false);
    fSetMuonsPerG4Event.AvailableForStates(G4State_Idle);
}

void PrimaryGeneratorMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    auto&& primaryGeneratorAction = RunManager::Instance().GetPrimaryGeneratorAction();
    if (command == std::addressof(fSetFlux)) {
        primaryGeneratorAction.SetFlux(fSetFlux.GetNewDoubleValue(value));
    } else if (command == std::addressof(fSetRepetitionRate)) {
        primaryGeneratorAction.SetRepetitionRate(fSetRepetitionRate.GetNewDoubleValue(value));
    } else if (command == std::addressof(fSetTimeWidthRMS)) {
        primaryGeneratorAction.SetTimeWidthRMS(fSetTimeWidthRMS.GetNewDoubleValue(value));
    } else if (command == std::addressof(fSetEnergy)) {
        primaryGeneratorAction.SetEnergy(fSetEnergy.GetNewDoubleValue(value));
    } else if (command == std::addressof(fSetEnergySpreadRMS)) {
        primaryGeneratorAction.SetEnergySpreadRMS(fSetEnergySpreadRMS.GetNewDoubleValue(value));
    } else if (command == std::addressof(fSetBeamProfileRMS)) {
        primaryGeneratorAction.SetBeamProfileRMS(fSetBeamProfileRMS.GetNewDoubleValue(value));
    } else if (command == std::addressof(fSetMuonsPerG4Event)) {
        primaryGeneratorAction.SetMuonsPerG4Event(fSetMuonsPerG4Event.GetNewIntValue(value));
    }
}
