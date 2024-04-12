#include "MACE/Detector/Description/ShieldingWall.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;
using namespace LiteralUnit::Angle;

ShieldingWall::ShieldingWall() :
    DescriptionBase{"ShieldingWall"},
    fEnabled{true},
    fThickness{50_cm},
    fLength{5_m},
    fRotation{30_deg} {}

auto ShieldingWall::ImportAllValue(const YAML::Node& node) -> void {
    ImportValue(node, fEnabled, "Enabled");
    ImportValue(node, fThickness, "Thickness");
    ImportValue(node, fLength, "Length");
    ImportValue(node, fRotation, "Rotation");
}

auto ShieldingWall::ExportAllValue(YAML::Node& node) const -> void {
    ExportValue(node, fEnabled, "Enabled");
    ExportValue(node, fThickness, "Thickness");
    ExportValue(node, fLength, "Length");
    ExportValue(node, fRotation, "Rotation");
}

} // namespace MACE::Detector::Description
