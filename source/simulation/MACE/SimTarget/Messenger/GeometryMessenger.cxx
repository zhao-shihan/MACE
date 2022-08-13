#include "MACE/Core/Geometry/Description/BeamDegrader.hxx"
#include "MACE/Core/Geometry/Description/BeamMonitor.hxx"
#include "MACE/Core/Geometry/Description/Target.hxx"
#include "MACE/Core/Geometry/Description/World.hxx"
#include "MACE/Core/Geometry/DescriptionIO.hxx"
#include "MACE/SimTarget/Action/DetectorConstruction.hxx"
#include "MACE/SimTarget/Messenger/GeometryMessenger.hxx"
#include "MACE/SimTarget/RunManager.hxx"

#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIdirectory.hh"

#include <string_view>

namespace MACE::SimTarget::Messenger {

GeometryMessenger::GeometryMessenger() :
    G4UImessenger(),
    fDetectorConstruction(nullptr),
    fImportDescription(),
    fExportDescription(),
    fIxportDescription(),
    fSetTargetDensity(),
    fSetTemperature() {

    fImportDescription = std::make_unique<G4UIcmdWithAString>("/MACE/Geometry/Description/Import", this);
    fImportDescription->SetGuidance("Import geometry descriptions required by this program from a yaml file.");
    fImportDescription->SetParameterName("yaml", false);
    fImportDescription->AvailableForStates(G4State_PreInit, G4State_Idle);

    fExportDescription = std::make_unique<G4UIcmdWithAString>("/MACE/Geometry/Description/Export", this);
    fExportDescription->SetGuidance("Export geometry descriptions used by this program to a yaml file.");
    fExportDescription->SetParameterName("yaml", false);
    fExportDescription->AvailableForStates(G4State_PreInit, G4State_Idle);

    fIxportDescription = std::make_unique<G4UIcmdWithAString>("/MACE/Geometry/Description/Ixport", this);
    fIxportDescription->SetGuidance("Import, then immediately export geometry descriptions used by this program.");
    fIxportDescription->SetParameterName("yaml", false);
    fIxportDescription->AvailableForStates(G4State_PreInit, G4State_Idle);

    fSetTargetDensity = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Geometry/SetTargetDensity", this);
    fSetTargetDensity->SetGuidance("Set target density.");
    fSetTargetDensity->SetParameterName("rho", false);
    fSetTargetDensity->SetUnitCategory("Volumic Mass");
    fSetTargetDensity->AvailableForStates(G4State_PreInit);

    fSetTemperature = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Geometry/SetTemperature", this);
    fSetTemperature->SetGuidance("Set environment temperature.");
    fSetTemperature->SetParameterName("T", false);
    fSetTemperature->SetUnitCategory("Temperature");
    fSetTemperature->AvailableForStates(G4State_PreInit);
}

GeometryMessenger::~GeometryMessenger() = default;

void GeometryMessenger::SetNewValue(ObserverPtr<G4UIcommand> command, G4String value) {
    using UsedDescriptions = Action::DetectorConstruction::UsedDescriptions;
    using Core::Geometry::DescriptionIO;
    if (command == fImportDescription.get()) {
        DescriptionIO::Import<UsedDescriptions>(std::string_view(value));
    } else if (command == fExportDescription.get()) {
        DescriptionIO::Export<UsedDescriptions>(std::string_view(value), "SimTarget: geometry description");
    } else if (command == fIxportDescription.get()) {
        DescriptionIO::Ixport<UsedDescriptions>(std::string_view(value), "SimTarget: geometry description");
    } else if (command == fSetTargetDensity.get()) {
        fDetectorConstruction->SetTargetDensity(fSetTargetDensity->GetNewDoubleValue(value));
    } else if (command == fSetTemperature.get()) {
        fDetectorConstruction->SetTemperature(fSetTemperature->GetNewDoubleValue(value));
    }
}

} // namespace MACE::SimTarget::Messenger
