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

namespace MACE::SimTarget::Messenger {

GeometryMessenger::GeometryMessenger() :
    G4UImessenger(),
    fDetectorConstruction(nullptr),
    // fSetWorldHalfExtent(nullptr),
    // fSetEnableBeamMonitor(nullptr),
    // fSetBeamMonitorWidth(nullptr),
    // fSetBeamMonitorThickness(nullptr),
    // fSetDistanceBetweenBeamMonitorAndTarget(nullptr),
    // fSetEnableDegrader(nullptr),
    // fSetDegraderWidth(nullptr),
    // fSetDegraderThickness(nullptr),
    // fSetDistanceBetweenDegraderAndTarget(nullptr),
    // fSetTargetWidth(nullptr),
    // fSetTargetThickness(nullptr),
    fImportDescription(),
    fExportDescription(),
    fSetTargetDensity(),
    fSetTemperature() {

    // fSetWorldHalfExtent = std::make_unique<G4UIcmdWith3VectorAndUnit>("/MACE/Geometry/SetWorldHalfExtent", this);
    // fSetWorldHalfExtent->SetGuidance("Set half extents of the world.");
    // fSetWorldHalfExtent->SetParameterName("x", "y", "z", false);
    // fSetWorldHalfExtent->SetUnitCategory("Length");
    // fSetWorldHalfExtent->AvailableForStates(G4State_PreInit);

    // fSetEnableBeamMonitor = std::make_unique<G4UIcmdWithABool>("/MACE/Geometry/SetEnableBeamMonitor", this);
    // fSetEnableBeamMonitor->SetGuidance("Set true to enable placement of beam monitor, and vice versa.");
    // fSetEnableBeamMonitor->SetParameterName("b", false);
    // fSetEnableBeamMonitor->AvailableForStates(G4State_PreInit);

    // fSetBeamMonitorWidth = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Geometry/SetBeamMonitorWidth", this);
    // fSetBeamMonitorWidth->SetGuidance("Set beam counter width.");
    // fSetBeamMonitorWidth->SetParameterName("w", false);
    // fSetBeamMonitorWidth->SetUnitCategory("Length");
    // fSetBeamMonitorWidth->AvailableForStates(G4State_PreInit);

    // fSetBeamMonitorThickness = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Geometry/SetBeamMonitorThickness", this);
    // fSetBeamMonitorThickness->SetGuidance("Set beam counter thickness.");
    // fSetBeamMonitorThickness->SetParameterName("t", false);
    // fSetBeamMonitorThickness->SetUnitCategory("Length");
    // fSetBeamMonitorThickness->AvailableForStates(G4State_PreInit);

    // fSetDistanceBetweenBeamMonitorAndTarget = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Geometry/SetDistanceBetweenBeamMonitorAndTarget", this);
    // fSetDistanceBetweenBeamMonitorAndTarget->SetGuidance("Set distance between beam monitor downstream surface and target upstream surface.");
    // fSetDistanceBetweenBeamMonitorAndTarget->SetParameterName("d", false);
    // fSetDistanceBetweenBeamMonitorAndTarget->SetUnitCategory("Length");
    // fSetDistanceBetweenBeamMonitorAndTarget->AvailableForStates(G4State_PreInit);

    // fSetEnableDegrader = std::make_unique<G4UIcmdWithABool>("/MACE/Geometry/SetEnableDegrader", this);
    // fSetEnableDegrader->SetGuidance("Set true to enable placement of beam degrader, and vice versa.");
    // fSetEnableDegrader->SetParameterName("b", false);
    // fSetEnableDegrader->AvailableForStates(G4State_PreInit);

    // fSetDegraderWidth = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Geometry/SetDegraderWidth", this);
    // fSetDegraderWidth->SetGuidance("Set beam degrader width.");
    // fSetDegraderWidth->SetParameterName("w", false);
    // fSetDegraderWidth->SetUnitCategory("Length");
    // fSetDegraderWidth->AvailableForStates(G4State_PreInit);

    // fSetDegraderThickness = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Geometry/SetDegraderThickness", this);
    // fSetDegraderThickness->SetGuidance("Set beam degrader thickness.");
    // fSetDegraderThickness->SetParameterName("t", false);
    // fSetDegraderThickness->SetUnitCategory("Length");
    // fSetDegraderThickness->AvailableForStates(G4State_PreInit);

    // fSetDistanceBetweenDegraderAndTarget = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Geometry/SetDistanceBetweenDegraderAndTarget", this);
    // fSetDistanceBetweenDegraderAndTarget->SetGuidance("Set distance between degrader downstream surface and target upstream surface.");
    // fSetDistanceBetweenDegraderAndTarget->SetParameterName("d", false);
    // fSetDistanceBetweenDegraderAndTarget->SetUnitCategory("Length");
    // fSetDistanceBetweenDegraderAndTarget->AvailableForStates(G4State_PreInit);

    // fSetTargetWidth = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Geometry/SetTargetWidth", this);
    // fSetTargetWidth->SetGuidance("Set target width.");
    // fSetTargetWidth->SetParameterName("w", false);
    // fSetTargetWidth->SetUnitCategory("Length");
    // fSetTargetWidth->AvailableForStates(G4State_PreInit);

    // fSetTargetThickness = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Geometry/SetTargetThickness", this);
    // fSetTargetThickness->SetGuidance("Set target thickness.");
    // fSetTargetThickness->SetParameterName("t", false);
    // fSetTargetThickness->SetUnitCategory("Length");
    // fSetTargetThickness->AvailableForStates(G4State_PreInit);

    fImportDescription = std::make_unique<G4UIcmdWithAString>("/MACE/Geometry/Description/Import", this);
    fImportDescription->SetGuidance("Import geometry descriptions required by this program from a yaml file.");
    fImportDescription->SetParameterName("yaml", false);
    fImportDescription->AvailableForStates(G4State_PreInit);

    fExportDescription = std::make_unique<G4UIcmdWithAString>("/MACE/Geometry/Description/Export", this);
    fExportDescription->SetGuidance("Export geometry descriptions used by this program to a yaml file.");
    fExportDescription->SetParameterName("yaml", false);
    fExportDescription->AvailableForStates(G4State_PreInit, G4State_Idle);

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

    // fSetAblationExtent = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Geometry/SetAblationExtent", this);
    // fSetAblationExtent->SetGuidance("Set the transverse range of the ablation area.");
    // fSetAblationExtent->SetParameterName("w", false);
    // fSetAblationExtent->SetUnitCategory("Length");
    // fSetAblationExtent->AvailableForStates(G4State_PreInit, G4State_Idle);

    // fSetHoleSpacing = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Geometry/SetHoleSpacing", this);
    // fSetHoleSpacing->SetGuidance("Set the closest distance between two adjacent ablation holes.");
    // fSetHoleSpacing->SetParameterName("s", false);
    // fSetHoleSpacing->SetUnitCategory("Length");
    // fSetHoleSpacing->AvailableForStates(G4State_PreInit, G4State_Idle);

    // fSetHoleDiameter = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Geometry/SetHoleDiameter", this);
    // fSetHoleDiameter->SetGuidance("Set the diameter of ablation holes.");
    // fSetHoleDiameter->SetParameterName("d", false);
    // fSetHoleDiameter->SetUnitCategory("Length");
    // fSetHoleDiameter->AvailableForStates(G4State_PreInit, G4State_Idle);

    // fSetHoleDepth = std::make_unique<G4UIcmdWithADoubleAndUnit>("/MACE/Geometry/SetHoleDepth", this);
    // fSetHoleDepth->SetGuidance("Set the depth of ablation holes.");
    // fSetHoleDepth->SetParameterName("d", false);
    // fSetHoleDepth->SetUnitCategory("Length");
    // fSetHoleDepth->AvailableForStates(G4State_PreInit, G4State_Idle);
}

void GeometryMessenger::SetNewValue(ObserverPtr<G4UIcommand> command, G4String value) {
    using namespace Core::Geometry;
    using DescriptionsToBeUsed = std::tuple<Description::BeamDegrader,
                                            Description::BeamMonitor,
                                            Description::Target,
                                            Description::World>;
    /* if (command == fSetWorldHalfExtent.get()) {
        auto& world = Description::World::Instance();
        auto halfExtent = fSetWorldHalfExtent->GetNew3VectorValue(value);
        world.SetHalfXExtent(halfExtent.x());
        world.SetHalfYExtent(halfExtent.y());
        world.SetHalfZExtent(halfExtent.z());
    } else if (command == fSetEnableBeamMonitor.get()) {
        Description::BeamMonitor::Instance().SetEnable(fSetEnableBeamMonitor->GetNewBoolValue(value));
    } else if (command == fSetBeamMonitorWidth.get()) {
        Description::BeamMonitor::Instance().SetWidth(fSetBeamMonitorWidth->GetNewDoubleValue(value));
    } else if (command == fSetBeamMonitorThickness.get()) {
        Description::BeamMonitor::Instance().SetThickness(fSetBeamMonitorThickness->GetNewDoubleValue(value));
    } else if (command == fSetDistanceBetweenBeamMonitorAndTarget.get()) {
        Description::BeamMonitor::Instance().SetDistanceToTargetSurface(fSetDistanceBetweenBeamMonitorAndTarget->GetNewDoubleValue(value));
    } else if (command == fSetEnableDegrader.get()) {
        Description::BeamDegrader::Instance().SetEnable(fSetEnableDegrader->GetNewBoolValue(value));
    } else if (command == fSetDegraderWidth.get()) {
        Description::BeamDegrader::Instance().SetWidth(fSetDegraderWidth->GetNewDoubleValue(value));
    } else if (command == fSetDegraderThickness.get()) {
        Description::BeamDegrader::Instance().SetThickness(fSetDegraderThickness->GetNewDoubleValue(value));
    } else if (command == fSetDistanceBetweenDegraderAndTarget.get()) {
        Description::BeamDegrader::Instance().SetDistanceToTargetSurface(fSetDistanceBetweenDegraderAndTarget->GetNewDoubleValue(value));
    } else if (command == fSetTargetWidth.get()) {
        Description::Target::Instance().GetCuboid().SetWidth(fSetTargetWidth->GetNewDoubleValue(value));
    } else if (command == fSetTargetThickness.get()) {
        Description::Target::Instance().GetCuboid().SetThickness(fSetTargetThickness->GetNewDoubleValue(value));
    } else  */
    if (command == fImportDescription.get()) {
        DescriptionIO::Import<DescriptionsToBeUsed>(value);
    } else if (command == fExportDescription.get()) {
        DescriptionIO::Export<DescriptionsToBeUsed>(value, "Geometry description exported from SimTarget.");
    } else if (command == fSetTargetDensity.get()) {
        fDetectorConstruction->SetTargetDensity(fSetTargetDensity->GetNewDoubleValue(value));
    } else if (command == fSetTemperature.get()) {
        fDetectorConstruction->SetTemperature(fSetTemperature->GetNewDoubleValue(value));
    }
    /* else if (command == fSetAblationExtent.get()) {
    Description::Target::Instance().GetCuboid().GetHole().SetExtent(fSetAblationExtent->GetNewDoubleValue(value));
} else if (command == fSetHoleSpacing.get()) {
    Description::Target::Instance().GetCuboid().GetHole().SetSpacing(fSetHoleSpacing->GetNewDoubleValue(value));
} else if (command == fSetHoleDiameter.get()) {
    Description::Target::Instance().GetCuboid().GetHole().SetDiameter(fSetHoleDiameter->GetNewDoubleValue(value));
} else if (command == fSetHoleDepth.get()) {
    Description::Target::Instance().GetCuboid().GetHole().SetDepth(fSetHoleDepth->GetNewDoubleValue(value));
} */
}

} // namespace MACE::SimTarget::Messenger
