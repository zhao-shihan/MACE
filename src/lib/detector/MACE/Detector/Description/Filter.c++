#include "MACE/Detector/Description/Filter.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;

Filter::Filter() :
    DescriptionSingletonBase<Filter>{"Filter"},
    fLength{50_cm},
    fRadius{49_mm},
    fThickness{200_um},
    fCount{85} {}

void Filter::ImportValues(const YAML::Node& node) {
    ImportValue(node, fLength, "Length");
    ImportValue(node, fRadius, "Radius");
    ImportValue(node, fThickness, "Thickness");
    ImportValue(node, fCount, "Count");
}

void Filter::ExportValues(YAML::Node& node) const {
    ExportValue(node, fLength, "Length");
    ExportValue(node, fRadius, "Radius");
    ExportValue(node, fThickness, "Thickness");
    ExportValue(node, fCount, "Count");
}

} // namespace MACE::Detector::Description
