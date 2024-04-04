#include "MACE/Detector/Description/Accelerator.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;
using namespace LiteralUnit::ElectricPotential;

Accelerator::Accelerator() :
    DescriptionSingletonBase{"Accelerator"},
    // Geometry
    fUpstreamLength{50_mm},
    fAccelerateLength{270_mm},
    fElectrodePitch{10_mm},
    fElectrodeInnerRadius{50_mm},
    fElectrodeOuterRadius{100_mm},
    fElectrodeThickness{0.5_mm},
    fFieldRadius{125_mm},
    // Material
    fElectrodeMaterialName{"G4_Be"},
    // Field
    fAcceleratePotential{500_V} {}

auto Accelerator::ImportValues(const YAML::Node& node) -> void {
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
    ImportValue(node, fAcceleratePotential, "AcceleratePotential");
}

auto Accelerator::ExportValues(YAML::Node& node) const -> void {
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
    ExportValue(node, fAcceleratePotential, "AcceleratePotential");
}

} // namespace MACE::Detector::Description
