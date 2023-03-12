#include "MACE/Core/Geometry/Description/Collimator.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

namespace MACE::Core::Geometry::Description {

using namespace LiteralUnit::Length;

Collimator::Collimator() :
    ISingletonDescription<Collimator>(__func__),
    fInnerRadius(5_mm),
    fOuterRadius(65_mm),
    fLength(30_cm),
    fAxialPosition(-20_cm),
    fThickness(0.75_mm),
    fCount(7) {}

void Collimator::ImportValues(const YAML::Node& node) {
    ImportValue(node, fInnerRadius, "InnerRadius");
    ImportValue(node, fOuterRadius, "OuterRadius");
    ImportValue(node, fLength, "Length");
    ImportValue(node, fAxialPosition, "AxialPosition");
    ImportValue(node, fThickness, "Thickness");
    ImportValue(node, fCount, "Count");
}

void Collimator::ExportValues(YAML::Node& node) const {
    ExportValue(node, fInnerRadius, "InnerRadius");
    ExportValue(node, fOuterRadius, "OuterRadius");
    ExportValue(node, fLength, "Length");
    ExportValue(node, fAxialPosition, "AxialPosition");
    ExportValue(node, fThickness, "Thickness");
    ExportValue(node, fCount, "Count");
}

} // namespace MACE::Core::Geometry::Description
