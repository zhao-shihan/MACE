#include "G4UIdirectory.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "SimMACE/Messenger/MuonBeamMessenger.hxx"
#include "SimMACE/Action/PrimaryGeneratorAction.hxx"

using namespace MACE::SimMACE::Messenger;

MuonBeamMessenger& MuonBeamMessenger::Instance() {
    static MuonBeamMessenger instance;
    return instance;
}

MuonBeamMessenger::MuonBeamMessenger() :
    G4UImessenger(),
    fDirectory("/MACE/MuonBeam/"),
    fSetFlux("/MACE/MuonBeam/SetFlux", this),
    fSetPlusePeakInterval("/MACE/MuonBeam/SetPlusePeakInterval", this),
    fSetPluseWidthRMS("/MACE/MuonBeam/SetPluseWidthRMS", this),
    fSetEnergy("/MACE/MuonBeam/SetEnergy", this),
    fSetEnergySpreadRMS("/MACE/MuonBeam/SetEnergySpreadRMS", this),
    fSetBeamWidthRMS("/MACE/MuonBeam/SetBeamWidthRMS", this) {

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

    fSetPlusePeakInterval.SetGuidance("Set time interval of pluse peak.");
    fSetPlusePeakInterval.SetParameterName("time interval", false);
    fSetPlusePeakInterval.SetUnitCategory("Time");
    fSetPlusePeakInterval.AvailableForStates(G4State_Idle);

    fSetPluseWidthRMS.SetGuidance("Set pluse width in time (RMS).");
    fSetPluseWidthRMS.SetParameterName("pluse width", false);
    fSetPluseWidthRMS.SetUnitCategory("Time");
    fSetPluseWidthRMS.AvailableForStates(G4State_Idle);

    fSetEnergy.SetGuidance("Set mean beam kinetic energy.");
    fSetEnergy.SetParameterName("energy", false);
    fSetEnergy.SetUnitCategory("Energy");
    fSetEnergy.AvailableForStates(G4State_Idle);

    fSetEnergySpreadRMS.SetGuidance("Set beam kinetic energy spread (RMS).");
    fSetEnergySpreadRMS.SetParameterName("energy spread", false);
    fSetEnergySpreadRMS.SetUnitCategory("Energy");
    fSetEnergySpreadRMS.AvailableForStates(G4State_Idle);

    fSetBeamWidthRMS.SetGuidance("Set beam width (RMS).");
    fSetBeamWidthRMS.SetParameterName("width (mm)", false);
    fSetBeamWidthRMS.SetUnitCategory("Length");
    fSetBeamWidthRMS.AvailableForStates(G4State_Idle);
}

void MuonBeamMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    if (command == std::addressof(fSetFlux)) {
        fPrimaryGeneratorAction->SetFlux(fSetFlux.GetNewDoubleValue(value));
    } else if (command == std::addressof(fSetPlusePeakInterval)) {
        fPrimaryGeneratorAction->SetPlusePeakInterval(fSetPlusePeakInterval.GetNewDoubleValue(value));
    } else if (command == std::addressof(fSetPluseWidthRMS)) {
        fPrimaryGeneratorAction->SetPluseWidthRMS(fSetPluseWidthRMS.GetNewDoubleValue(value));
    } else if (command == std::addressof(fSetEnergy)) {
        fPrimaryGeneratorAction->SetEnergy(fSetEnergy.GetNewDoubleValue(value));
    } else if (command == std::addressof(fSetEnergySpreadRMS)) {
        fPrimaryGeneratorAction->SetEnergySpreadRMS(fSetEnergySpreadRMS.GetNewDoubleValue(value));
    } else if (command == std::addressof(fSetBeamWidthRMS)) {
        fPrimaryGeneratorAction->SetBeamWidthRMS(fSetBeamWidthRMS.GetNewDoubleValue(value));
    }
}
