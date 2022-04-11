#include "MACE/Simulation/Generator/SurfaceMuon/GeneratorMessenger.hxx"
#include "MACE/Simulation/Generator/SurfaceMuon/PrimaryGeneratorAction.hxx"

#include "G4SystemOfUnits.hh"
#include "G4UIdirectory.hh"
#include "G4UnitsTable.hh"

namespace MACE::Simulation::Generator::SurfaceMuon {

GeneratorMessenger& GeneratorMessenger::Instance() {
    static GeneratorMessenger instance;
    return instance;
}

GeneratorMessenger::GeneratorMessenger() :
    G4UImessenger(),
    fDirectory("/MACE/Generator/SurfaceMuon/"),
    fSetFlux("/MACE/Generator/SurfaceMuon/SetFlux", this),
    fSetRepetitionRate("/MACE/Generator/SurfaceMuon/SetRepetitionRate", this),
    fSetTimeWidthRMS("/MACE/Generator/SurfaceMuon/SetTimeWidthRMS", this),
    fSetEnergy("/MACE/Generator/SurfaceMuon/SetEnergy", this),
    fSetEnergySpreadRMS("/MACE/Generator/SurfaceMuon/SetEnergySpreadRMS", this),
    fSetBeamProfileRMS("/MACE/Generator/SurfaceMuon/SetBeamProfileRMS", this),
    fSetVertexZ("/MACE/Generator/SurfaceMuon/SetVertexZ", this),
    fSetMuonsForEachG4Event("/MACE/Generator/SurfaceMuon/SetMuonsForEachG4Event", this) {

    // Introduce some useful units.
    // per unit time (for beam flux)
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

    fSetVertexZ.SetGuidance("It does what you think it does.");
    fSetVertexZ.SetParameterName("z position", false);
    fSetVertexZ.SetUnitCategory("Length");
    fSetVertexZ.AvailableForStates(G4State_Idle);

    fSetMuonsForEachG4Event.SetGuidance("Set muons generated for each G4 event. Beam properties won't be affected unless the value is greater than muons per repetition. In common case, a few hundred to thousand is OK.");
    fSetMuonsForEachG4Event.SetParameterName("n", false);
    fSetMuonsForEachG4Event.AvailableForStates(G4State_Idle);
}

void GeneratorMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    if (command == std::addressof(fSetFlux)) {
        fPrimaryGeneratorAction->SetFlux(fSetFlux.GetNewDoubleValue(value));
    } else if (command == std::addressof(fSetRepetitionRate)) {
        fPrimaryGeneratorAction->SetRepetitionRate(fSetRepetitionRate.GetNewDoubleValue(value));
    } else if (command == std::addressof(fSetTimeWidthRMS)) {
        fPrimaryGeneratorAction->SetTimeWidthRMS(fSetTimeWidthRMS.GetNewDoubleValue(value));
    } else if (command == std::addressof(fSetEnergy)) {
        fPrimaryGeneratorAction->SetEnergy(fSetEnergy.GetNewDoubleValue(value));
    } else if (command == std::addressof(fSetEnergySpreadRMS)) {
        fPrimaryGeneratorAction->SetEnergySpreadRMS(fSetEnergySpreadRMS.GetNewDoubleValue(value));
    } else if (command == std::addressof(fSetBeamProfileRMS)) {
        fPrimaryGeneratorAction->SetBeamProfileRMS(fSetBeamProfileRMS.GetNewDoubleValue(value));
    } else if (command == std::addressof(fSetVertexZ)) {
        fPrimaryGeneratorAction->SetVertexZ(fSetVertexZ.GetNewDoubleValue(value));
    } else if (command == std::addressof(fSetMuonsForEachG4Event)) {
        fPrimaryGeneratorAction->SetMuonsForEachG4Event(fSetMuonsForEachG4Event.GetNewIntValue(value));
    }
}

} // namespace MACE::Simulation::Generator::SurfaceMuon
