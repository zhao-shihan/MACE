#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Utility/LiteralUnit.h++"
#include "MACE/Utility/MathConstant.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;
using namespace LiteralUnit::MagneticFluxDensity;
using namespace MathConstant;

Solenoid::Solenoid() :
    DescriptionSingletonBase{"Solenoid"},
    // Geometry
    fS1Length{15_cm},
    fB1Radius{25_cm},
    fS2Length{131.5_cm},
    fB2Radius{25_cm},
    fS3Length{15_cm},
    fInnerRadius{50_mm},
    fOuterRadius{100_mm},
    fFieldRadius{101_mm},
    // Material
    fMaterialName{"G4_Cu"},
    // Field
    fMagneticFluxDensity(100_mT) {}

auto Solenoid::ImportValues(const YAML::Node& node) -> void {
    // Geometry
    ImportValue(node, fS1Length, "S1Length");
    ImportValue(node, fB1Radius, "B1Radius");
    ImportValue(node, fS2Length, "S2Length");
    ImportValue(node, fB2Radius, "B2Radius");
    ImportValue(node, fS3Length, "S3Length");
    ImportValue(node, fInnerRadius, "InnerRadius");
    ImportValue(node, fOuterRadius, "OuterRadius");
    ImportValue(node, fFieldRadius, "FieldRadius");
    // Material
    ImportValue(node, fMaterialName, "MaterialName");
    // Field
    ImportValue(node, fMagneticFluxDensity, "MagneticFluxDensity");
}

auto Solenoid::ExportValues(YAML::Node& node) const -> void {
    // Geometry
    ExportValue(node, fS1Length, "S1Length");
    ExportValue(node, fB1Radius, "B1Radius");
    ExportValue(node, fS2Length, "S2Length");
    ExportValue(node, fB2Radius, "B2Radius");
    ExportValue(node, fS3Length, "S3Length");
    ExportValue(node, fInnerRadius, "InnerRadius");
    ExportValue(node, fOuterRadius, "OuterRadius");
    ExportValue(node, fFieldRadius, "FieldRadius");
    // Material
    ExportValue(node, fMaterialName, "MaterialName");
    // Field
    ExportValue(node, fMagneticFluxDensity, "MagneticFluxDensity");
}

} // namespace MACE::Detector::Description
