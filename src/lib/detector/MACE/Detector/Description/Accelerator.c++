#include "MACE/Detector/Description/Accelerator.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;
using namespace LiteralUnit::ElectricPotential;

Accelerator::Accelerator() :
    DescriptionSingletonBase{"Accelerator"},
    // Geometry
    fRadius{75_mm},
    fUpstreamLength{100_mm},
    fAccelerateLength{270_mm},
    // Field
    fAcceleratePotential{500_V},
    // Cached value
    fAcceleratorFieldStrength{fAcceleratePotential / fAccelerateLength} {}

auto Accelerator::ImportValues(const YAML::Node& node) -> void {
    // Geometry
    ImportValue(node, fRadius, "Radius");
    ImportValue(node, fUpstreamLength, "UpstreamLength");
    ImportValue(node, fAccelerateLength, "AccelerateLength");
    // Field
    ImportValue(node, fAcceleratePotential, "AcceleratePotential");
}

auto Accelerator::ExportValues(YAML::Node& node) const -> void {
    // Geometry
    ExportValue(node, fRadius, "Radius");
    ExportValue(node, fUpstreamLength, "UpstreamLength");
    ExportValue(node, fAccelerateLength, "AccelerateLength");
    // Field
    ExportValue(node, fAcceleratePotential, "AcceleratePotential");
}

} // namespace MACE::Detector::Description
