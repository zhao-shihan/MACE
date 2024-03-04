#include "MACE/Detector/Description/SpectrometerShield.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;
using namespace LiteralUnit::Angle;

SpectrometerShield::SpectrometerShield() :
    DescriptionSingletonBase<SpectrometerShield>{"SpectrometerShield"},
    fInnerRadius{62_cm},
    fInnerLength{222_cm},
    fThickness{5_cm},
    fWindowRadius{3_cm},
    fBeamSlantAngle{0_deg} {}

void SpectrometerShield::ImportValues(const YAML::Node& node) {
    ImportValue(node, fInnerRadius, "InnerRadius");
    ImportValue(node, fInnerLength, "InnerLength");
    ImportValue(node, fThickness, "Thickness");
    ImportValue(node, fWindowRadius, "WindowRadius");
    ImportValue(node, fBeamSlantAngle, "BeamSlantAngle");
}

void SpectrometerShield::ExportValues(YAML::Node& node) const {
    ExportValue(node, fInnerRadius, "InnerRadius");
    ExportValue(node, fInnerLength, "InnerLength");
    ExportValue(node, fThickness, "Thickness");
    ExportValue(node, fWindowRadius, "WindowRadius");
    ExportValue(node, fBeamSlantAngle, "BeamSlantAngle");
}

} // namespace MACE::Detector::Description
