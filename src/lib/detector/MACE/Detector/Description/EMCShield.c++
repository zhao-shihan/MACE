#include "MACE/Detector/Description/EMCShield.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;

EMCShield::EMCShield() :
    DescriptionSingletonBase{"EMCShield"},
    // Geometry
    fInnerRadius{65_cm},
    fInnerLength{110_cm},
    fGapAroundWindow{1_cm},
    fThickness{5_cm},
    // Material
    fMaterialName{"G4_Pb"} {}

auto EMCShield::ImportValues(const YAML::Node& node) -> void {
    // Geometry
    ImportValue(node, fInnerRadius, "InnerRadius");
    ImportValue(node, fInnerLength, "InnerLength");
    ImportValue(node, fGapAroundWindow, "GapAroundWindow");
    ImportValue(node, fThickness, "Thickness");
    // Material
    ImportValue(node, fMaterialName, "MaterialName");
}

auto EMCShield::ExportValues(YAML::Node& node) const -> void {
    // Geometry
    ExportValue(node, fInnerRadius, "InnerRadius");
    ExportValue(node, fInnerLength, "InnerLength");
    ExportValue(node, fGapAroundWindow, "GapAroundWindow");
    ExportValue(node, fThickness, "Thickness");
    // Material
    ExportValue(node, fMaterialName, "MaterialName");
}

} // namespace MACE::Detector::Description
