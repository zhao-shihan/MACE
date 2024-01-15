#include "MACE/Detector/Description/ShieldingWall.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;

ShieldingWall::ShieldingWall() :
    DescriptionSingletonBase<ShieldingWall>("ShieldingWall"),
    fThickness{50_cm} {}

auto ShieldingWall::ImportValues(const YAML::Node& node) -> void {
    ImportValue(node, fThickness, "Thickness");
}

auto ShieldingWall::ExportValues(YAML::Node& node) const -> void {
    ExportValue(node, fThickness, "Thickness");
}

} // namespace MACE::Detector::Description
