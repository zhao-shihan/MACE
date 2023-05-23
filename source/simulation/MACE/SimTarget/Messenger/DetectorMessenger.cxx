#include "MACE/Detector/Description/BeamDegrader.hxx"
#include "MACE/Detector/Description/BeamMonitor.hxx"
#include "MACE/Detector/Description/Target.hxx"
#include "MACE/Detector/Description/World.hxx"
#include "MACE/Detector/Description/DescriptionIO.hxx"
#include "MACE/SimTarget/Action/DetectorConstruction.hxx"
#include "MACE/SimTarget/Messenger/DetectorMessenger.hxx"
#include "MACE/SimTarget/RunManager.hxx"

#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIdirectory.hh"

#include <string_view>

namespace MACE::SimTarget::inline Messenger {

GeometryMessenger::GeometryMessenger() :
    G4UImessenger(),
    fDetectorConstruction(nullptr),
    fDirectory(),
    fImportDescription(),
    fExportDescription(),
    fIxportDescription(),
    fTargetDensity(),
    fTemperature() {

    fDirectory = std::make_unique<G4UIdirectory>("/MACE/Detector/");

    fImportDescription = std::make_unique<G4UIcmdWithAString>("/MACE/Detector/Description/Import", this);
    fImportDescription->SetGuidance("Import geometry descriptions required by this program from a yaml file.");
    fImportDescription->SetParameterName("yaml", false);
    fImportDescription->AvailableForStates(G4State_PreInit, G4State_Idle);

    fExportDescription = std::make_unique<G4UIcmdWithAString>("/MACE/Detector/Description/Export", this);
    fExportDescription->SetGuidance("Export geometry descriptions used by this program to a yaml file.");
    fExportDescription->SetParameterName("yaml", false);
    fExportDescription->AvailableForStates(G4State_PreInit, G4State_Idle);

    fIxportDescription = std::make_unique<G4UIcmdWithAString>("/MACE/Detector/Description/Ixport", this);
    fIxportDescription->SetGuidance("Import, then immediately export geometry descriptions used by this program.");
    fIxportDescription->SetParameterName("yaml", false);
    fIxportDescription->AvailableForStates(G4State_PreInit, G4State_Idle);

    fTargetDensity = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Detector/TargetDensity", this);
    fTargetDensity->SetGuidance("Set target density.");
    fTargetDensity->SetParameterName("rho", false);
    fTargetDensity->SetUnitCategory("Volumic Mass");
    fTargetDensity->AvailableForStates(G4State_PreInit);

    fTemperature = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Detector/Temperature", this);
    fTemperature->SetGuidance("Set environment temperature.");
    fTemperature->SetParameterName("T", false);
    fTemperature->SetUnitCategory("Temperature");
    fTemperature->AvailableForStates(G4State_PreInit);
}

GeometryMessenger::~GeometryMessenger() = default;

void GeometryMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    using DescriptionInUse = DetectorConstruction::DescriptionInUse;
    using Detector::Description::DescriptionIO;
    if (command == fImportDescription.get()) {
        DescriptionIO::Import<DescriptionInUse>(std::string_view(value));
    } else if (command == fExportDescription.get()) {
        DescriptionIO::Export<DescriptionInUse>(std::string_view(value), "SimTarget: geometry description");
    } else if (command == fIxportDescription.get()) {
        DescriptionIO::Ixport<DescriptionInUse>(std::string_view(value), "SimTarget: geometry description");
    } else if (command == fTargetDensity.get()) {
        fDetectorConstruction->SetTargetDensity(fTargetDensity->GetNewDoubleValue(value));
    } else if (command == fTemperature.get()) {
        fDetectorConstruction->SetTemperature(fTemperature->GetNewDoubleValue(value));
    }
}

} // namespace MACE::SimTarget::inline Messenger
