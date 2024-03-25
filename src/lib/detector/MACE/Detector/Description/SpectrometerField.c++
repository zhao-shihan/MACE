#include "MACE/Detector/Description/SpectrometerField.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;
using namespace LiteralUnit::MagneticFluxDensity;

SpectrometerField::SpectrometerField() :
    DescriptionSingletonBase{"SpectrometerField"},
    // Geometry
    fRadius{61_cm},
    fLength{220_cm},
    // Field
    fMagneticFluxDensity{100_mT} {}

void SpectrometerField::ImportValues(const YAML::Node& node) {
    // Geometry
    ImportValue(node, fRadius, "Radius");
    ImportValue(node, fLength, "Length");
    // Field
    ImportValue(node, fMagneticFluxDensity, "MagneticFluxDensity");
}

void SpectrometerField::ExportValues(YAML::Node& node) const {
    // Geometry
    ExportValue(node, fRadius, "Radius");
    ExportValue(node, fLength, "Length");
    // Field
    ExportValue(node, fMagneticFluxDensity, "MagneticFluxDensity");
}

} // namespace MACE::Detector::Description
