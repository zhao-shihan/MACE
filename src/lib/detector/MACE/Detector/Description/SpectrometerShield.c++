#include "MACE/Detector/Description/SpectrometerShield.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;

SpectrometerShield::SpectrometerShield() :
    DescriptionSingletonBase<SpectrometerShield>{"SpectrometerShield"},
    fInnerRadius{62_cm},
    fInnerLength{222_cm},
    fGapAroundWindow{1_cm},
    fThickness{5_cm} {}

void SpectrometerShield::ImportValues(const YAML::Node& node) {
    ImportValue(node, fInnerRadius, "InnerRadius");
    ImportValue(node, fInnerLength, "InnerLength");
    ImportValue(node, fGapAroundWindow, "GapAroundWindow");
    ImportValue(node, fThickness, "Thickness");
}

void SpectrometerShield::ExportValues(YAML::Node& node) const {
    ExportValue(node, fInnerRadius, "InnerRadius");
    ExportValue(node, fInnerLength, "InnerLength");
    ExportValue(node, fGapAroundWindow, "GapAroundWindow");
    ExportValue(node, fThickness, "Thickness");
}

} // namespace MACE::Detector::Description
