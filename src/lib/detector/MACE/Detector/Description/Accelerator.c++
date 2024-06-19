#include "MACE/Detector/Description/Accelerator.h++"

#include "Mustard/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace Mustard::LiteralUnit::Length;
using namespace Mustard::LiteralUnit::ElectricFieldStrength;

Accelerator::Accelerator() :
    DescriptionBase{"Accelerator"},
    // Geometry
    fUpstreamLength{110_mm},
    fAccelerateLength{270_mm},
    fElectrodePitch{20_mm},
    fElectrodeInnerRadius{50_mm},
    fElectrodeOuterRadius{60_mm},
    fElectrodeThickness{0.5_mm},
    fFieldRadius{70_mm},
    // Material
    fElectrodeMaterialName{"G4_Be"},
    // Field
    fFastField{1670_V_m} {}

auto Accelerator::ImportAllValue(const YAML::Node& node) -> void {
    // Geometry
    ImportValue(node, fUpstreamLength, "UpstreamLength");
    ImportValue(node, fAccelerateLength, "AccelerateLength");
    ImportValue(node, fElectrodePitch, "ElectrodePitch");
    ImportValue(node, fElectrodeInnerRadius, "ElectrodeInnerRadius");
    ImportValue(node, fElectrodeOuterRadius, "ElectrodeOuterRadius");
    ImportValue(node, fElectrodeThickness, "ElectrodeThickness");
    ImportValue(node, fFieldRadius, "FieldRadius");
    // Material
    ImportValue(node, fElectrodeMaterialName, "ElectrodeMaterialName");
    // Field
    ImportValue(node, fFastField, "FastField");
}

auto Accelerator::ExportAllValue(YAML::Node& node) const -> void {
    // Geometry
    ExportValue(node, fUpstreamLength, "UpstreamLength");
    ExportValue(node, fAccelerateLength, "AccelerateLength");
    ExportValue(node, fElectrodePitch, "ElectrodePitch");
    ExportValue(node, fElectrodeInnerRadius, "ElectrodeInnerRadius");
    ExportValue(node, fElectrodeOuterRadius, "ElectrodeOuterRadius");
    ExportValue(node, fElectrodeThickness, "ElectrodeThickness");
    ExportValue(node, fFieldRadius, "FieldRadius");
    // Material
    ExportValue(node, fElectrodeMaterialName, "ElectrodeMaterialName");
    // Field
    ExportValue(node, fFastField, "FastField");
}

} // namespace MACE::Detector::Description
