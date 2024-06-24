#include "MACE/Detector/Description/Accelerator.h++"

#include "Mustard/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace Mustard::LiteralUnit::ElectricPotential;
using namespace Mustard::LiteralUnit::Length;

Accelerator::Accelerator() :
    DescriptionBase{"Accelerator"},
    // Geometry
    fUpstreamLength{110_mm},
    fDownstreamLength{270_mm},
    fElectrodePitch{20_mm},
    fElectrodeInnerRadius{50_mm},
    fElectrodeOuterRadius{60_mm},
    fElectrodeThickness{0.5_mm},
    fFieldRadius{70_mm},
    // Material
    fElectrodeMaterialName{"G4_Be"},
    // Field
    fMaxPotential{586.7_V},
    fMaxPotentialPosition{-65_mm},
    fDecelerateLength{165_mm},
    fAccelerateLength{360_mm} {}

auto Accelerator::ImportAllValue(const YAML::Node& node) -> void {
    // Geometry
    ImportValue(node, fUpstreamLength, "UpstreamLength");
    ImportValue(node, fDownstreamLength, "DownstreamLength");
    ImportValue(node, fElectrodePitch, "ElectrodePitch");
    ImportValue(node, fElectrodeInnerRadius, "ElectrodeInnerRadius");
    ImportValue(node, fElectrodeOuterRadius, "ElectrodeOuterRadius");
    ImportValue(node, fElectrodeThickness, "ElectrodeThickness");
    ImportValue(node, fFieldRadius, "FieldRadius");
    // Material
    ImportValue(node, fElectrodeMaterialName, "ElectrodeMaterialName");
    // Field
    ImportValue(node, fMaxPotential, "MaxPotential");
    ImportValue(node, fMaxPotentialPosition, "MaxPotentialPosition");
    ImportValue(node, fDecelerateLength, "DecelerateLength");
    ImportValue(node, fAccelerateLength, "AccelerateLength");
}

auto Accelerator::ExportAllValue(YAML::Node& node) const -> void {
    // Geometry
    ExportValue(node, fUpstreamLength, "UpstreamLength");
    ExportValue(node, fDownstreamLength, "DownstreamLength");
    ExportValue(node, fElectrodePitch, "ElectrodePitch");
    ExportValue(node, fElectrodeInnerRadius, "ElectrodeInnerRadius");
    ExportValue(node, fElectrodeOuterRadius, "ElectrodeOuterRadius");
    ExportValue(node, fElectrodeThickness, "ElectrodeThickness");
    ExportValue(node, fFieldRadius, "FieldRadius");
    // Material
    ExportValue(node, fElectrodeMaterialName, "ElectrodeMaterialName");
    // Field
    ExportValue(node, fMaxPotential, "MaxPotential");
    ExportValue(node, fMaxPotentialPosition, "MaxPotentialPosition");
    ExportValue(node, fDecelerateLength, "DecelerateLength");
    ExportValue(node, fAccelerateLength, "AccelerateLength");
}

} // namespace MACE::Detector::Description
