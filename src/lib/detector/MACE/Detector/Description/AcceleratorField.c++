#include "MACE/Detector/Description/AcceleratorField.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;
using namespace LiteralUnit::ElectricPotential;

AcceleratorField::AcceleratorField() :
    DescriptionSingletonBase{"AcceleratorField"},
    // Geometry
    fRadius{75_mm},
    fLength{50_cm},
    fAccelerateLength{30_cm},
    // Field
    fAcceleratorPotential{500_V},
    // Cached value
    fAcceleratorFieldStrength{fAcceleratorPotential / fAccelerateLength} {}

auto AcceleratorField::ImportValues(const YAML::Node& node) -> void {
    // Geometry
    ImportValue(node, fRadius, "Radius");
    ImportValue(node, fLength, "Length");
    ImportValue(node, fAccelerateLength, "AccelerateLength");
    // Field
    ImportValue(node, fAcceleratorPotential, "AcceleratorPotential");
}

auto AcceleratorField::ExportValues(YAML::Node& node) const -> void {
    // Geometry
    ExportValue(node, fRadius, "Radius");
    ExportValue(node, fLength, "Length");
    ExportValue(node, fAccelerateLength, "AccelerateLength");
    // Field
    ExportValue(node, fAcceleratorPotential, "AcceleratorPotential");
}

} // namespace MACE::Detector::Description
