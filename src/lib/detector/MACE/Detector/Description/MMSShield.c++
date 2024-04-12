#include "MACE/Detector/Description/MMSShield.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;
using namespace LiteralUnit::Angle;

MMSShield::MMSShield() :
    DescriptionBase{"MMSShield"},
    // Geometry
    fInnerRadius{65_cm},
    fInnerLength{230_cm},
    fThickness{5_cm},
    fWindowRadius{132_mm},
    fBeamSlantAngle{0_deg},
    // Material
    fMaterialName{"G4_Fe"} {}

auto MMSShield::ImportAllValue(const YAML::Node& node) -> void {
    // Geometry
    ImportValue(node, fInnerRadius, "InnerRadius");
    ImportValue(node, fInnerLength, "InnerLength");
    ImportValue(node, fThickness, "Thickness");
    ImportValue(node, fWindowRadius, "WindowRadius");
    ImportValue(node, fBeamSlantAngle, "BeamSlantAngle");
    // Material
    ImportValue(node, fMaterialName, "MaterialName");
}

auto MMSShield::ExportAllValue(YAML::Node& node) const -> void {
    // Geometry
    ExportValue(node, fInnerRadius, "InnerRadius");
    ExportValue(node, fInnerLength, "InnerLength");
    ExportValue(node, fThickness, "Thickness");
    ExportValue(node, fWindowRadius, "WindowRadius");
    ExportValue(node, fBeamSlantAngle, "BeamSlantAngle");
    // Material
    ExportValue(node, fMaterialName, "MaterialName");
}

} // namespace MACE::Detector::Description
