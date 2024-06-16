#include "MACE/Detector/Description/Solenoid.h++"
#include "Mustard/Utility/LiteralUnit.h++"
#include "Mustard/Utility/MathConstant.h++"

namespace MACE::Detector::Description {

using namespace Mustard::LiteralUnit::Length;
using namespace Mustard::LiteralUnit::MagneticFluxDensity;
using namespace Mustard::MathConstant;

Solenoid::Solenoid() :
    DescriptionBase{"Solenoid"},
    // Geometry
    fS1Length{150_mm},
    fT1Radius{250_mm},
    fS2Length{1314.6_mm},
    fT2Radius{250_mm},
    fS3Length{150_mm},
    fInnerRadius{60_mm},
    fOuterRadius{90_mm},
    fCoilThickness{30_mm},
    fReferenceCoilSpacing{30_mm},
    fFieldRadius{131_mm},
    // Material
    fMaterialName{"G4_Cu"},
    // Field
    fFastField{100_mT} {}

auto Solenoid::ImportAllValue(const YAML::Node& node) -> void {
    // Geometry
    ImportValue(node, fS1Length, "S1Length");
    ImportValue(node, fT1Radius, "T1Radius");
    ImportValue(node, fS2Length, "S2Length");
    ImportValue(node, fT2Radius, "T2Radius");
    ImportValue(node, fS3Length, "S3Length");
    ImportValue(node, fInnerRadius, "InnerRadius");
    ImportValue(node, fOuterRadius, "OuterRadius");
    ImportValue(node, fCoilThickness, "CoilThickness");
    ImportValue(node, fReferenceCoilSpacing, "ReferenceCoilSpacing");
    ImportValue(node, fFieldRadius, "FieldRadius");
    // Material
    ImportValue(node, fMaterialName, "MaterialName");
    // Field
    ImportValue(node, fFastField, "FastField");
}

auto Solenoid::ExportAllValue(YAML::Node& node) const -> void {
    // Geometry
    ExportValue(node, fS1Length, "S1Length");
    ExportValue(node, fT1Radius, "T1Radius");
    ExportValue(node, fS2Length, "S2Length");
    ExportValue(node, fT2Radius, "T2Radius");
    ExportValue(node, fS3Length, "S3Length");
    ExportValue(node, fInnerRadius, "InnerRadius");
    ExportValue(node, fOuterRadius, "OuterRadius");
    ExportValue(node, fCoilThickness, "CoilThickness");
    ExportValue(node, fReferenceCoilSpacing, "ReferenceCoilSpacing");
    ExportValue(node, fFieldRadius, "FieldRadius");
    // Material
    ExportValue(node, fMaterialName, "MaterialName");
    // Field
    ExportValue(node, fFastField, "FastField");
}

} // namespace MACE::Detector::Description
