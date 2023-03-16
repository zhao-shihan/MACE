#include "MACE/Detector/Description/SpectrometerShield.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;

SpectrometerShield::SpectrometerShield() :
    DescriptionSingletonBase<SpectrometerShield>(__func__),
    fInnerRadius(72_cm),
    fInnerLength(222_cm),
    fWindowRadius(12.7_cm),
    fThickness(5_cm) {}

void SpectrometerShield::ImportValues(const YAML::Node& node) {
    ImportValue(node, fInnerRadius, "InnerRadius");
    ImportValue(node, fInnerLength, "InnerLength");
    ImportValue(node, fWindowRadius, "WindowRadius");
    ImportValue(node, fThickness, "Thickness");
}

void SpectrometerShield::ExportValues(YAML::Node& node) const {
    ExportValue(node, fInnerRadius, "InnerRadius");
    ExportValue(node, fInnerLength, "InnerLength");
    ExportValue(node, fWindowRadius, "WindowRadius");
    ExportValue(node, fThickness, "Thickness");
}

} // namespace MACE::Detector::Description
