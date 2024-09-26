#include "MACE/Detector/Description/ECALShield.h++"
#include "MACE/Detector/Description/Solenoid.h++"

#include "Mustard/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace Mustard::LiteralUnit::Length;

ECALShield::ECALShield() :
    DescriptionBase{"ECALShield"},
    // Geometry
    fInnerRadius{60_cm},
    fInnerLength{110_cm},
    fGapAroundWindow{1_cm},
    fThickness{5_cm},
    // Material
    fMaterialName{"G4_Fe"} {}

auto ECALShield::ImportAllValue(const YAML::Node& node) -> void {
    // Geometry
    ImportValue(node, fInnerRadius, "InnerRadius");
    ImportValue(node, fInnerLength, "InnerLength");
    ImportValue(node, fGapAroundWindow, "GapAroundWindow");
    ImportValue(node, fThickness, "Thickness");
    // Material
    ImportValue(node, fMaterialName, "MaterialName");
}

auto ECALShield::ExportAllValue(YAML::Node& node) const -> void {
    // Geometry
    ExportValue(node, fInnerRadius, "InnerRadius");
    ExportValue(node, fInnerLength, "InnerLength");
    ExportValue(node, fGapAroundWindow, "GapAroundWindow");
    ExportValue(node, fThickness, "Thickness");
    // Material
    ExportValue(node, fMaterialName, "MaterialName");
}

} // namespace MACE::Detector::Description
