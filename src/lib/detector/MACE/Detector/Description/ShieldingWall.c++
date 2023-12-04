#include "MACE/Detector/Description/ShieldingWall.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;

ShieldingWall::ShieldingWall() :
    DescriptionSingletonBase<ShieldingWall>("ShieldingWall"),
    fHeight{2_m},
    fWidth{4_m},
    fThickness{30_cm} {}

auto ShieldingWall::ImportValues(const YAML::Node& node) -> void {
    ImportValue(node, fHeight, "Height");
    ImportValue(node, fWidth, "Width");
    ImportValue(node, fThickness, "Thickness");
}

auto ShieldingWall::ExportValues(YAML::Node& node) const -> void {
    ExportValue(node, fHeight, "Height");
    ExportValue(node, fWidth, "Width");
    ExportValue(node, fThickness, "Thickness");
}

} // namespace MACE::Detector::Description
