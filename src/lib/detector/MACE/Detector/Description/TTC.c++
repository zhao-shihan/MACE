#include "MACE/Detector/Description/TTC.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Time;
using namespace LiteralUnit::Length;
using namespace LiteralUnit::Angle;

TTC::TTC() :
    DescriptionSingletonBase{"TTC"},
    // Geometry
    fLength{15_cm},
    fWidth{10_cm},
    fThickness{1_cm},
    fRadius{48_cm},
    fSlantAngle{15_deg},
    fNAlongPhi{42},
    fNAlongZ{18},
    // Material
    fMaterialName{"G4_PLASTIC_SC_VINYLTOLUENE"},
    // Detection
    fTimeResolutionFWHM{50_ps} {}

auto TTC::ImportValues(const YAML::Node& node) -> void {
    // Geometry
    ImportValue(node, fLength, "Length");
    ImportValue(node, fWidth, "Width");
    ImportValue(node, fThickness, "Thickness");
    ImportValue(node, fRadius, "DistanceToCDC");
    ImportValue(node, fSlantAngle, "SlantAngle");
    ImportValue(node, fNAlongPhi, "NAlongPhi");
    ImportValue(node, fNAlongZ, "NAlongZ");
    // Material
    ImportValue(node, fMaterialName, "MaterialName");
    // Detection
    ImportValue(node, fTimeResolutionFWHM, "TimeResolutionFWHM");
}

auto TTC::ExportValues(YAML::Node& node) const -> void {
    // Geometry
    ExportValue(node, fLength, "Length");
    ExportValue(node, fWidth, "Width");
    ExportValue(node, fThickness, "Thickness");
    ExportValue(node, fRadius, "DistanceToCDC");
    ExportValue(node, fSlantAngle, "SlantAngle");
    ExportValue(node, fNAlongPhi, "NAlongPhi");
    ExportValue(node, fNAlongZ, "NAlongZ");
    // Material
    ExportValue(node, fMaterialName, "MaterialName");
    // Detection
    ExportValue(node, fTimeResolutionFWHM, "TimeResolutionFWHM");
}

} // namespace MACE::Detector::Description
