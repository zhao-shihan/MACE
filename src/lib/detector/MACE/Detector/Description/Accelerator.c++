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
    fDecelerateFieldLength{165_mm},
    fAccelerateFieldLength{360_mm},
    // Material
    fElectrodeMaterialName{"G4_Be"},
    // Field
    fMaxPotential{586.7_V},
    fMaxPotentialPosition{-65_mm} {}

auto Accelerator::ImportAllValue(const YAML::Node& node) -> void {
    // Geometry
    ImportValue(node, fUpstreamLength, "UpstreamLength");
    ImportValue(node, fDownstreamLength, "DownstreamLength");
    ImportValue(node, fElectrodePitch, "ElectrodePitch");
    ImportValue(node, fElectrodeInnerRadius, "ElectrodeInnerRadius");
    ImportValue(node, fElectrodeOuterRadius, "ElectrodeOuterRadius");
    ImportValue(node, fElectrodeThickness, "ElectrodeThickness");
    ImportValue(node, fFieldRadius, "FieldRadius");
    ImportValue(node, fDecelerateFieldLength, "DecelerateFieldLength");
    ImportValue(node, fAccelerateFieldLength, "AccelerateFieldLength");
    // Material
    ImportValue(node, fElectrodeMaterialName, "ElectrodeMaterialName");
    // Field
    ImportValue(node, fMaxPotential, "MaxPotential");
    ImportValue(node, fMaxPotentialPosition, "MaxPotentialPosition");
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
    ExportValue(node, fDecelerateFieldLength, "DecelerateFieldLength");
    ExportValue(node, fAccelerateFieldLength, "AccelerateFieldLength");
    // Material
    ExportValue(node, fElectrodeMaterialName, "ElectrodeMaterialName");
    // Field
    ExportValue(node, fMaxPotential, "MaxPotential");
    ExportValue(node, fMaxPotentialPosition, "MaxPotentialPosition");
}

} // namespace MACE::Detector::Description
