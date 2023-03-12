#include "MACE/Core/Geometry/Description/SpectrometerMagnet.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

namespace MACE::Core::Geometry::Description {

using namespace LiteralUnit::Length;

SpectrometerMagnet::SpectrometerMagnet() :
    ISingletonDescription<SpectrometerMagnet>(__func__),
    fInnerRadius(50_cm),
    fOuterRadius(70_cm),
    fLength(218_cm) {}

void SpectrometerMagnet::ImportValues(const YAML::Node& node) {
    ImportValue(node, fInnerRadius, "InnerRadius");
    ImportValue(node, fOuterRadius, "OuterRadius");
    ImportValue(node, fLength, "Length");
}

void SpectrometerMagnet::ExportValues(YAML::Node& node) const {
    ExportValue(node, fInnerRadius, "InnerRadius");
    ExportValue(node, fOuterRadius, "OuterRadius");
    ExportValue(node, fLength, "Length");
}

} // namespace MACE::Core::Geometry::Description
