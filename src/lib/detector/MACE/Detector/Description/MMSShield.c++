#include "MACE/Detector/Description/MMSShield.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;
using namespace LiteralUnit::Angle;

MMSShield::MMSShield() :
    DescriptionSingletonBase{"MMSShield"},
    // Geometry
    fInnerRadius{62_cm},
    fInnerLength{224_cm},
    fThickness{5_cm},
    fWindowRadius{3_cm},
    fBeamSlantAngle{0_deg},
    // Material
    fMaterialName{"G4_Pb"} {}

auto MMSShield::ImportValues(const YAML::Node& node) -> void {
    // Geometry
    ImportValue(node, fInnerRadius, "InnerRadius");
    ImportValue(node, fInnerLength, "InnerLength");
    ImportValue(node, fThickness, "Thickness");
    ImportValue(node, fWindowRadius, "WindowRadius");
    ImportValue(node, fBeamSlantAngle, "BeamSlantAngle");
    // Material
    ImportValue(node, fMaterialName, "MaterialName");
}

auto MMSShield::ExportValues(YAML::Node& node) const -> void {
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
