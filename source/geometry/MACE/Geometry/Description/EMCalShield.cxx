#include "MACE/Geometry/Description/EMCalShield.hxx"
#include "MACE/Geometry/Description/TransportLine.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

namespace MACE::Geometry::Description {

using namespace LiteralUnit::Length;

EMCalShield::EMCalShield() :
    ISingletonDescription<EMCalShield>(__func__),
    fInnerRadius(30_cm),
    fInnerLength(80_cm),
    fWindowRadius(12.7_cm),
    fThickness(5_cm) {}

void EMCalShield::ImportValues(const YAML::Node& node) {
    ImportValue(node, fInnerRadius, "InnerRadius");
    ImportValue(node, fInnerLength, "InnerLength");
    ImportValue(node, fWindowRadius, "WindowRadius");
    ImportValue(node, fThickness, "Thickness");
}

void EMCalShield::ExportValues(YAML::Node& node) const {
    ExportValue(node, fInnerRadius, "InnerRadius");
    ExportValue(node, fInnerLength, "InnerLength");
    ExportValue(node, fWindowRadius, "WindowRadius");
    ExportValue(node, fThickness, "Thickness");
}

} // namespace MACE::Geometry::Description
