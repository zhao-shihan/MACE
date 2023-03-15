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
    fMomentum(),
    fMomentumRMS(),
    fPositionRMS(),
    fPositionZ() {

    fDirectory = std::make_unique<G4UIdirectory>("/MACE/Generator/SurfaceMuon/");
    fDirectory->SetGuidance("MACE muon beam.");

    fMomentum = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Generator/SurfaceMuon/Momentum", this);
    fMomentum->SetGuidance("Set mean beam momentum.");
    fMomentum->SetParameterName("p", false);
    fMomentum->SetUnitCategory("Energy");
    fMomentum->AvailableForStates(G4State_Idle);

    fMomentumRMS = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Generator/SurfaceMuon/MomentumRMS", this);
    fMomentumRMS->SetGuidance("Set beam momentum spread (RMS).");
    fMomentumRMS->SetParameterName("sigma_p", false);
    fMomentumRMS->SetUnitCategory("Energy");
    fMomentumRMS->AvailableForStates(G4State_Idle);

    fPositionRMS = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Generator/SurfaceMuon/PositionRMS", this);
    fPositionRMS->SetGuidance("Set beam profile width (RMS).");
    fPositionRMS->SetParameterName("sigma", false);
    fPositionRMS->SetUnitCategory("Length");
    fPositionRMS->AvailableForStates(G4State_Idle);

    fPositionZ = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Generator/SurfaceMuon/VertexZ", this);
    fPositionZ->SetGuidance("It does what you think it does.");
    fPositionZ->SetParameterName("z", false);
    fPositionZ->SetUnitCategory("Length");
    fPositionZ->AvailableForStates(G4State_Idle);
}

SurfaceMuonMessenger::~SurfaceMuonMessenger() = default;

void SurfaceMuonMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    if (command == fMomentum.get()) {
        fSurfaceMuonGenerator->Momentum(fMomentum->GetNewDoubleValue(value));
    } else if (command == fMomentumRMS.get()) {
        fSurfaceMuonGenerator->MomentumRMS(fMomentumRMS->GetNewDoubleValue(value));
    } else if (command == fPositionRMS.get()) {
        fSurfaceMuonGenerator->PositionRMS(fPositionRMS->GetNewDoubleValue(value));
    } else if (command == fPositionZ.get()) {
        fSurfaceMuonGenerator->PositionZ(fPositionZ->GetNewDoubleValue(value));
    }
}

} // namespace MACE::inline Extension::Geant4X::Generator
