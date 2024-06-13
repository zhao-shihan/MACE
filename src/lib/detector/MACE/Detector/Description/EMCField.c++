#include "MACE/Detector/Description/EMCField.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;
using namespace LiteralUnit::MagneticFluxDensity;

EMCField::EMCField() : // clang-format off
    DescriptionBase{"EMCField"}, // clang-format on
    // Geometry
    fRadius{56_cm},
    fLength{100_cm},
    // Field
    fFastField{0.1_T} {}

auto EMCField::ImportAllValue(const YAML::Node& node) -> void {
    // Geometry
    ImportValue(node, fRadius, "Radius");
    ImportValue(node, fLength, "Length");
    // Field
    ImportValue(node, fFastField, "FastField");
}

auto EMCField::ExportAllValue(YAML::Node& node) const -> void {
    // Geometry
    ExportValue(node, fRadius, "Radius");
    ExportValue(node, fLength, "Length");
    // Field
    ExportValue(node, fFastField, "FastField");
}

} // namespace MACE::Detector::Description
