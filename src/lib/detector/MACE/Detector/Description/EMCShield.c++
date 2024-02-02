#include "MACE/Detector/Description/EMCShield.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;

EMCShield::EMCShield() :
    DescriptionSingletonBase<EMCShield>{"EMCShield"},
    fInnerRadius{60_cm},
    fInnerLength{100_cm},
    fGapAroundWindow{1_cm},
    fThickness{5_cm} {}

auto EMCShield::ImportValues(const YAML::Node& node) -> void {
    ImportValue(node, fInnerRadius, "InnerRadius");
    ImportValue(node, fInnerLength, "InnerLength");
    ImportValue(node, fGapAroundWindow, "GapAroundWindow");
    ImportValue(node, fThickness, "Thickness");
}

auto EMCShield::ExportValues(YAML::Node& node) const -> void {
    ExportValue(node, fInnerRadius, "InnerRadius");
    ExportValue(node, fInnerLength, "InnerLength");
    ExportValue(node, fGapAroundWindow, "GapAroundWindow");
    ExportValue(node, fThickness, "Thickness");
}

} // namespace MACE::Detector::Description
