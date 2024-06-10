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
    fField{} {}

EMCField::FieldType::FieldType() :
    fUseFast{false},
    fFastField{0.1_T},
    fFieldMap{"${MACE_FIELD_DATA}"} {}

auto EMCField::ImportAllValue(const YAML::Node& node) -> void {
    // Geometry
    ImportValue(node, fRadius, "Radius");
    ImportValue(node, fLength, "Length");
    // Field
    ImportValue(node, fField.fUseFast, "Field", "UseFast");
    ImportValue(node, fField.fFastField, "Field", "FastField");
    ImportValue(node, fField.fFieldMap, "Field", "FieldMap");
}

auto EMCField::ExportAllValue(YAML::Node& node) const -> void {
    // Geometry
    ExportValue(node, fRadius, "Radius");
    ExportValue(node, fLength, "Length");
    // Field
    ExportValue(node, fField.fUseFast, "Field", "UseFast");
    ExportValue(node, fField.fFastField, "Field", "FastField");
    ExportValue(node, fField.fFieldMap, "Field", "FieldMap");
}

} // namespace MACE::Detector::Description
