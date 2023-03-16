#include "MACE/Detector/Description/SelectorField.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;

SelectorField::SelectorField() :
    DescriptionSingletonBase<SelectorField>(__func__),
    fRadius(7.5_cm),
    fLength(30_cm),
    fAxialPosition(20_cm) {}

void SelectorField::ImportValues(const YAML::Node& node) {
    ImportValue(node, fRadius, "Radius");
    ImportValue(node, fLength, "Length");
    ImportValue(node, fAxialPosition, "AxialPosition");
}

void SelectorField::ExportValues(YAML::Node& node) const {
    ExportValue(node, fRadius, "Radius");
    ExportValue(node, fLength, "Length");
    ExportValue(node, fAxialPosition, "AxialPosition");
}

} // namespace MACE::Detector::Description
