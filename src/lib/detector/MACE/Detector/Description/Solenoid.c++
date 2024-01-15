#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Utility/LiteralUnit.h++"
#include "MACE/Utility/MathConstant.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;
using namespace LiteralUnit::MagneticFluxDensity;
using namespace MathConstant;

Solenoid::Solenoid() :
    DescriptionSingletonBase<Solenoid>{"Solenoid"},
    // Geometry
    fS1Length{20_cm},
    fB1Radius{50_cm},
    fS2Length{100_cm},
    fB2Radius{50_cm},
    fS3Length{20_cm},
    fInnerRadius{25_mm},
    fOuterRadius{75_mm},
    fFieldRadius{76_mm},
    // Field
    fMagneticFluxDensity(100_mT) {}

void Solenoid::ImportValues(const YAML::Node& node) {
    // Geometry
    ImportValue(node, fS1Length, "S1Length");
    ImportValue(node, fB1Radius, "B1Radius");
    ImportValue(node, fS2Length, "S2Length");
    ImportValue(node, fB2Radius, "B2Radius");
    ImportValue(node, fS3Length, "S3Length");
    ImportValue(node, fInnerRadius, "InnerRadius");
    ImportValue(node, fOuterRadius, "OuterRadius");
    ImportValue(node, fFieldRadius, "FieldRadius");
    // Field
    ImportValue(node, fMagneticFluxDensity, "MagneticFluxDensity");
}

void Solenoid::ExportValues(YAML::Node& node) const {
    // Geometry
    ExportValue(node, fS1Length, "S1Length");
    ExportValue(node, fB1Radius, "B1Radius");
    ExportValue(node, fS2Length, "S2Length");
    ExportValue(node, fB2Radius, "B2Radius");
    ExportValue(node, fS3Length, "S3Length");
    ExportValue(node, fInnerRadius, "InnerRadius");
    ExportValue(node, fOuterRadius, "OuterRadius");
    ExportValue(node, fFieldRadius, "FieldRadius");
    // Field
    ExportValue(node, fMagneticFluxDensity, "MagneticFluxDensity");
}

} // namespace MACE::Detector::Description
