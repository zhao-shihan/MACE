#include "MACE/Detector/Description/ECalField.h++"
#include "MACE/Detector/Description/Solenoid.h++"

#include "Mustard/Utility/LiteralUnit.h++"
#include "Mustard/Utility/VectorArithmeticOperator.h++"

namespace MACE::Detector::Description {

using namespace Mustard::LiteralUnit::Length;
using namespace Mustard::LiteralUnit::MagneticFluxDensity;

ECalField::ECalField() : // clang-format off
    DescriptionBase{"ECalField"}, // clang-format on
    // Geometry
    fRadius{60_cm},
    fLength{100_cm},
    // Field
    fFastField{0.1_T} {}

auto ECalField::Center() const -> muc::array3d {
    using namespace Mustard::VectorArithmeticOperator;
    const auto& solenoid{Solenoid::Instance()};
    return solenoid.S3Center() + muc::array3d{0, 0, (solenoid.S3Length() + fLength) / 2};
}

auto ECalField::ImportAllValue(const YAML::Node& node) -> void {
    // Geometry
    ImportValue(node, fRadius, "Radius");
    ImportValue(node, fLength, "Length");
    // Field
    ImportValue(node, fFastField, "FastField");
}

auto ECalField::ExportAllValue(YAML::Node& node) const -> void {
    // Geometry
    ExportValue(node, fRadius, "Radius");
    ExportValue(node, fLength, "Length");
    // Field
    ExportValue(node, fFastField, "FastField");
}

} // namespace MACE::Detector::Description
