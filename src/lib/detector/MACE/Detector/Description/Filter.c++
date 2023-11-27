#include "MACE/Detector/Description/Filter.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;

Filter::Filter() :
    DescriptionSingletonBase<Filter>("Filter"),
    fLength(100_cm),
    fWidth(3.5_cm),
    fThickness(200_um),
    fCount(32) {}

void Filter::ImportValues(const YAML::Node& node) {
    ImportValue(node, fLength, "Length");
    ImportValue(node, fWidth, "Width");
    ImportValue(node, fThickness, "Thickness");
    ImportValue(node, fCount, "Count");
}

void Filter::ExportValues(YAML::Node& node) const {
    ExportValue(node, fLength, "Length");
    ExportValue(node, fWidth, "Width");
    ExportValue(node, fThickness, "Thickness");
    ExportValue(node, fCount, "Count");
}

} // namespace MACE::Detector::Description
