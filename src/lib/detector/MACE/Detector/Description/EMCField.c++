#include "MACE/Detector/Description/EMCField.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;
using namespace LiteralUnit::MagneticFluxDensity;

EMCField::EMCField() :
    DescriptionSingletonBase<EMCField>(__func__),
    // Geometry
    fRadius{47_cm},
    fLength{95_cm},
    // Field
    fMagneticFluxDensity{100_mT} {}

auto EMCField::ImportValues(const YAML::Node& node) -> void {
    // Geometry
    ImportValue(node, fRadius, "Radius");
    ImportValue(node, fLength, "Length");
    // Field
    ImportValue(node, fMagneticFluxDensity, "MagneticFluxDensity");
}

auto EMCField::ExportValues(YAML::Node& node) const -> void {
    // Geometry
    ExportValue(node, fRadius, "Radius");
    ExportValue(node, fLength, "Length");
    // Field
    ExportValue(node, fMagneticFluxDensity, "MagneticFluxDensity");
}

} // namespace MACE::Detector::Description
