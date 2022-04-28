#include "MACE/Simulation/Generator/SurfaceMuonMessenger.hxx"
#include "MACE/Simulation/Generator/SurfaceMuon.hxx"

#include "G4SystemOfUnits.hh"
#include "G4UIdirectory.hh"
#include "G4UnitsTable.hh"

namespace MACE::Simulation::Generator {

SurfaceMuonMessenger& SurfaceMuonMessenger::Instance() {
    static SurfaceMuonMessenger instance;
    return instance;
}

SurfaceMuonMessenger::SurfaceMuonMessenger() :
    G4UImessenger(),
    fDirectory("/MACE/Generator/SurfaceMuon/"),
    fSetMomentum("/MACE/Generator/SurfaceMuon/SetMomentum", this),
    fSetMomentumSpreadRMS("/MACE/Generator/SurfaceMuon/SetMomentumSpreadRMS", this),
    fSetBeamProfileRMS("/MACE/Generator/SurfaceMuon/SetBeamProfileRMS", this),
    fSetVertexZ("/MACE/Generator/SurfaceMuon/SetVertexZ", this) {

    fDirectory.SetGuidance("MACE muon beam.");

    fSetMomentum.SetGuidance("Set mean beam momentum.");
    fSetMomentum.SetParameterName("p", false);
    fSetMomentum.SetUnitCategory("Energy");
    fSetMomentum.AvailableForStates(G4State_Idle);

    fSetMomentumSpreadRMS.SetGuidance("Set beam momentum spread (RMS).");
    fSetMomentumSpreadRMS.SetParameterName("sigma_p", false);
    fSetMomentumSpreadRMS.SetUnitCategory("Energy");
    fSetMomentumSpreadRMS.AvailableForStates(G4State_Idle);

    fSetBeamProfileRMS.SetGuidance("Set beam profile width (RMS).");
    fSetBeamProfileRMS.SetParameterName("sigma", false);
    fSetBeamProfileRMS.SetUnitCategory("Length");
    fSetBeamProfileRMS.AvailableForStates(G4State_Idle);

    fSetVertexZ.SetGuidance("It does what you think it does.");
    fSetVertexZ.SetParameterName("z", false);
    fSetVertexZ.SetUnitCategory("Length");
    fSetVertexZ.AvailableForStates(G4State_Idle);
}

void SurfaceMuonMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    if (command == std::addressof(fSetMomentum)) {
        fSurfaceMuonGenerator->SetMomentum(fSetMomentum.GetNewDoubleValue(value));
    } else if (command == std::addressof(fSetMomentumSpreadRMS)) {
        fSurfaceMuonGenerator->SetMomentumSpreadRMS(fSetMomentumSpreadRMS.GetNewDoubleValue(value));
    } else if (command == std::addressof(fSetBeamProfileRMS)) {
        fSurfaceMuonGenerator->SetBeamProfileRMS(fSetBeamProfileRMS.GetNewDoubleValue(value));
    } else if (command == std::addressof(fSetVertexZ)) {
        fSurfaceMuonGenerator->SetVertexZ(fSetVertexZ.GetNewDoubleValue(value));
    }
}

} // namespace MACE::Simulation::Generator
