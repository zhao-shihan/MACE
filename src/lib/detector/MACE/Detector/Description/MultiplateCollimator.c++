#include "MACE/Detector/Description/MultiplateCollimator.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;

MultiplateCollimator::MultiplateCollimator() :
    DescriptionSingletonBase<MultiplateCollimator>(__func__),
    fLength(100_cm),
    fWidth(10_cm),
    fThickness(500_um),
    fCount(11) {}

void MultiplateCollimator::ImportValues(const YAML::Node& node) {
    ImportValue(node, fLength, "Length");
    ImportValue(node, fWidth, "Width");
    ImportValue(node, fThickness, "Thickness");
    ImportValue(node, fCount, "Count");
}

void MultiplateCollimator::ExportValues(YAML::Node& node) const {
    ExportValue(node, fLength, "Length");
    ExportValue(node, fWidth, "Width");
    ExportValue(node, fThickness, "Thickness");
    ExportValue(node, fCount, "Count");
}

} // namespace MACE::Detector::Description
