#include "MACE/Geometry/Description/EMCal.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

namespace MACE::Geometry::Description {

using namespace LiteralUnit::Length;

EMCal::EMCal() :
    ISingletonDescription<EMCal>(__func__),
    fInnerRadius(15_cm),
    fInnerLength(50_cm),
    fWindowRadius(8_cm),
    fCrystalLength(5_cm) {}

void EMCal::ImportValues(const YAML::Node& node) {
    ImportValue(node, fInnerRadius, "InnerRadius");
    ImportValue(node, fInnerLength, "InnerLength");
    ImportValue(node, fWindowRadius, "WindowRadius");
    ImportValue(node, fCrystalLength, "CrystalLength");
}

void EMCal::ExportValues(YAML::Node& node) const {
    ExportValue(node, fInnerRadius, "InnerRadius");
    ExportValue(node, fInnerLength, "InnerLength");
    ExportValue(node, fWindowRadius, "WindowRadius");
    ExportValue(node, fCrystalLength, "CrystalLength");
}

} // namespace MACE::Geometry::Description
