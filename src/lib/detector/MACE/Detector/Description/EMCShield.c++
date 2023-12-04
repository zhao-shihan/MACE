#include "MACE/Detector/Description/EMCShield.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;

EMCShield::EMCShield() :
    DescriptionSingletonBase<EMCShield>(__func__),
    fInnerRadius{50_cm},
    fInnerLength{100_cm},
    fWindowRadius{7.7_cm},
    fThickness{5_cm} {}

auto EMCShield::ImportValues(const YAML::Node& node) -> void {
    ImportValue(node, fInnerRadius, "InnerRadius");
    ImportValue(node, fInnerLength, "InnerLength");
    ImportValue(node, fWindowRadius, "WindowRadius");
    ImportValue(node, fThickness, "Thickness");
}

auto EMCShield::ExportValues(YAML::Node& node) const -> void {
    ExportValue(node, fInnerRadius, "InnerRadius");
    ExportValue(node, fInnerLength, "InnerLength");
    ExportValue(node, fWindowRadius, "WindowRadius");
    ExportValue(node, fThickness, "Thickness");
}

} // namespace MACE::Detector::Description
