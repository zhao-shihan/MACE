#include "MACE/Extension/Geant4X/Generator/SurfaceMuon.hxx"
#include "MACE/Extension/Geant4X/Generator/SurfaceMuonMessenger.hxx"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIdirectory.hh"

namespace MACE::inline Extension::Geant4X::Generator {

SurfaceMuonMessenger::SurfaceMuonMessenger() :
    Singleton(),
    G4UImessenger(),
    fSurfaceMuonGenerator(nullptr),
    fDirectory(),
    fSetMomentum(),
    fSetMomentumSpreadRMS(),
    fSetBeamProfileRMS(),
    fSetVertexZ() {

    fDirectory = std::make_unique<G4UIdirectory>("/MACE/Generator/SurfaceMuon/");
    fDirectory->SetGuidance("MACE muon beam.");

    fSetMomentum = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Generator/SurfaceMuon/SetMomentum", this);
    fSetMomentum->SetGuidance("Set mean beam momentum.");
    fSetMomentum->SetParameterName("p", false);
    fSetMomentum->SetUnitCategory("Energy");
    fSetMomentum->AvailableForStates(G4State_Idle);

    fSetMomentumSpreadRMS = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Generator/SurfaceMuon/SetMomentumSpreadRMS", this);
    fSetMomentumSpreadRMS->SetGuidance("Set beam momentum spread (RMS).");
    fSetMomentumSpreadRMS->SetParameterName("sigma_p", false);
    fSetMomentumSpreadRMS->SetUnitCategory("Energy");
    fSetMomentumSpreadRMS->AvailableForStates(G4State_Idle);

    fSetBeamProfileRMS = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Generator/SurfaceMuon/SetBeamProfileRMS", this);
    fSetBeamProfileRMS->SetGuidance("Set beam profile width (RMS).");
    fSetBeamProfileRMS->SetParameterName("sigma", false);
    fSetBeamProfileRMS->SetUnitCategory("Length");
    fSetBeamProfileRMS->AvailableForStates(G4State_Idle);

    fSetVertexZ = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Generator/SurfaceMuon/SetVertexZ", this);
    fSetVertexZ->SetGuidance("It does what you think it does.");
    fSetVertexZ->SetParameterName("z", false);
    fSetVertexZ->SetUnitCategory("Length");
    fSetVertexZ->AvailableForStates(G4State_Idle);
}

SurfaceMuonMessenger::~SurfaceMuonMessenger() = default;

void SurfaceMuonMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    if (command == fSetMomentum.get()) {
        fSurfaceMuonGenerator->Momentum(fSetMomentum->GetNewDoubleValue(value));
    } else if (command == fSetMomentumSpreadRMS.get()) {
        fSurfaceMuonGenerator->MomentumSpreadRMS(fSetMomentumSpreadRMS->GetNewDoubleValue(value));
    } else if (command == fSetBeamProfileRMS.get()) {
        fSurfaceMuonGenerator->BeamProfileRMS(fSetBeamProfileRMS->GetNewDoubleValue(value));
    } else if (command == fSetVertexZ.get()) {
        fSurfaceMuonGenerator->VertexZ(fSetVertexZ->GetNewDoubleValue(value));
    }
}

} // namespace MACE::inline Extension::Geant4X::Generator
