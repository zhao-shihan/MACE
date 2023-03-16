#include "MACE/Detector/Description/SpectrometerField.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;

SpectrometerField::SpectrometerField() :
    DescriptionSingletonBase<SpectrometerField>(__func__),
    fRadius(71_cm),
    fLength(220_cm) {}

void SpectrometerField::ImportValues(const YAML::Node& node) {
    ImportValue(node, fRadius, "Radius");
    ImportValue(node, fLength, "Length");
}

void SpectrometerField::ExportValues(YAML::Node& node) const {
    ExportValue(node, fRadius, "Radius");
    ExportValue(node, fLength, "Length");
}

} // namespace MACE::Geometry::Description
