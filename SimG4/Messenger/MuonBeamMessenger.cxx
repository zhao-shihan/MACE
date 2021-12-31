#include "G4UIdirectory.hh"
#include "G4UnitsTable.hh"

#include "SimG4/Messenger/MuonBeamMessenger.hxx"
#include "SimG4/Action/PrimaryGeneratorAction.hxx"

using namespace MACE::SimG4::Messenger;

MuonBeamMessenger* MuonBeamMessenger::Instance() {
    static MuonBeamMessenger instance;
    return &instance;
}

MuonBeamMessenger::MuonBeamMessenger() :
    G4UImessenger(),
    fpPrimaryGeneratorAction(nullptr) {

    // Introduce some useful units.
    // per second (for beam flux)
    new G4UnitDefinition("second^-1", "s^-1", "Time^-1", 1.0 / second);
    new G4UnitDefinition("millisecond^-1", "ms^-1", "Time^-1", 1.0 / millisecond);
    new G4UnitDefinition("microsecond^-1", "us^-1", "Time^-1", 1.0 / microsecond);
    new G4UnitDefinition("nanosecond^-1", "ns^-1", "Time^-1", 1.0 / nanosecond);
    new G4UnitDefinition("picosecond^-1", "ps^-1", "Time^-1", 1.0 / picosecond);

    fDirectory = new G4UIdirectory("/MACE/MuonBeam/");
    fDirectory->SetGuidance("MACE muon beam.");

    fSetFlux = new G4UIcmdWithADoubleAndUnit("/MACE/MuonBeam/SetFlux", this);
    fSetFlux->SetGuidance("Set muon flux.");
    fSetFlux->SetParameterName("flux", false);
    fSetFlux->SetUnitCategory("Time^-1");
    fSetFlux->AvailableForStates(G4State_Idle);

    fSetPlusePeakInterval = new G4UIcmdWithADoubleAndUnit("/MACE/MuonBeam/SetPlusePeakInterval", this);
    fSetPlusePeakInterval->SetGuidance("Set time interval of pluse peak.");
    fSetPlusePeakInterval->SetParameterName("time interval", false);
    fSetPlusePeakInterval->SetUnitCategory("Time");
    fSetPlusePeakInterval->AvailableForStates(G4State_Idle);

    fSetPluseWidthRMS = new G4UIcmdWithADoubleAndUnit("/MACE/MuonBeam/SetPluseWidthRMS", this);
    fSetPluseWidthRMS->SetGuidance("Set pluse width in time (RMS).");
    fSetPluseWidthRMS->SetParameterName("pluse width", false);
    fSetPluseWidthRMS->SetUnitCategory("Time");
    fSetPluseWidthRMS->AvailableForStates(G4State_Idle);

    fSetEnergy = new G4UIcmdWithADoubleAndUnit("/MACE/MuonBeam/SetEnergy", this);
    fSetEnergy->SetGuidance("Set mean beam kinetic energy.");
    fSetEnergy->SetParameterName("energy", false);
    fSetEnergy->SetUnitCategory("Energy");
    fSetEnergy->AvailableForStates(G4State_Idle);

    fSetEnergySpreadRMS = new G4UIcmdWithADoubleAndUnit("/MACE/MuonBeam/SetEnergySpreadRMS", this);
    fSetEnergySpreadRMS->SetGuidance("Set beam kinetic energy spread (RMS).");
    fSetEnergySpreadRMS->SetParameterName("energy spread", false);
    fSetEnergySpreadRMS->SetUnitCategory("Energy");
    fSetEnergySpreadRMS->AvailableForStates(G4State_Idle);

    fSetBeamWidthRMS = new G4UIcmdWithADoubleAndUnit("/MACE/MuonBeam/SetBeamWidthRMS", this);
    fSetBeamWidthRMS->SetGuidance("Set beam width (RMS).");
    fSetBeamWidthRMS->SetParameterName("width (mm)", false);
    fSetBeamWidthRMS->SetUnitCategory("Length");
    fSetBeamWidthRMS->AvailableForStates(G4State_Idle);
}

MuonBeamMessenger::~MuonBeamMessenger() {
    delete fSetFlux;
    delete fSetPlusePeakInterval;
    delete fSetPluseWidthRMS;
    delete fSetEnergy;
    delete fSetEnergySpreadRMS;
    delete fSetBeamWidthRMS;
    delete fDirectory;
}

void MuonBeamMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    if (command == fSetFlux) {
        fpPrimaryGeneratorAction->SetFlux(fSetFlux->GetNewDoubleValue(value));
    } else if (command == fSetPlusePeakInterval) {
        fpPrimaryGeneratorAction->SetPlusePeakInterval(fSetPlusePeakInterval->GetNewDoubleValue(value));
    } else if (command == fSetPluseWidthRMS) {
        fpPrimaryGeneratorAction->SetPluseWidthRMS(fSetPluseWidthRMS->GetNewDoubleValue(value));
    } else if (command == fSetEnergy) {
        fpPrimaryGeneratorAction->SetEnergy(fSetEnergy->GetNewDoubleValue(value));
    } else if (command == fSetEnergySpreadRMS) {
        fpPrimaryGeneratorAction->SetEnergySpreadRMS(fSetEnergySpreadRMS->GetNewDoubleValue(value));
    } else if (command == fSetBeamWidthRMS) {
        fpPrimaryGeneratorAction->SetBeamWidthRMS(fSetBeamWidthRMS->GetNewDoubleValue(value));
    }
}


