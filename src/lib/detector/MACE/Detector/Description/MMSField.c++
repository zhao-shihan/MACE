#include "MACE/Detector/Description/MMSField.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;
using namespace LiteralUnit::MagneticFluxDensity;

MMSField::MMSField() :
    DescriptionBase{"MMSField"},
    // Geometry
    fRadius{61_cm},
    fLength{220_cm},
    // Field
    fFastField{100_mT} {}

void MMSField::ImportAllValue(const YAML::Node& node) {
    // Geometry
    ImportValue(node, fRadius, "Radius");
    ImportValue(node, fLength, "Length");
    // Field
    ImportValue(node, fFastField, "FastField");
}

void MMSField::ExportAllValue(YAML::Node& node) const {
    // Geometry
    ExportValue(node, fRadius, "Radius");
    ExportValue(node, fLength, "Length");
    // Field
    ExportValue(node, fFastField, "FastField");
}

} // namespace MACE::Detector::Description
