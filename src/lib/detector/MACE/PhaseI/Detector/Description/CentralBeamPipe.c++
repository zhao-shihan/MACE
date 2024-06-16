#include "MACE/PhaseI/Detector/Description/CentralBeamPipe.h++"

#include "Mustard/Utility/LiteralUnit.h++"

namespace MACE::PhaseI::Detector::Description {

using namespace Mustard::LiteralUnit::Length;
using namespace Mustard::LiteralUnit::Pressure;

CentralBeamPipe::CentralBeamPipe() :
    DescriptionBase{"CentralBeamPipe"},
    // Geometry
    fLength{1000_mm},
    fInnerRadius{40_mm},
    fBerylliumLength{200_mm},
    fBerylliumThickness{500_um},
    fAluminiumThickness{2_mm},
    // Material
    fVacuumPressure{1e-4_Pa} {}

auto CentralBeamPipe::ImportAllValue(const YAML::Node& node) -> void {
    // Geometry
    ImportValue(node, fLength, "Length");
    ImportValue(node, fInnerRadius, "InnerRadius");
    ImportValue(node, fBerylliumLength, "BerylliumLength");
    ImportValue(node, fBerylliumThickness, "BerylliumThickness");
    ImportValue(node, fAluminiumThickness, "AluminiumThickness");
    // Material
    ImportValue(node, fVacuumPressure, "VacuumPressure");
}

auto CentralBeamPipe::ExportAllValue(YAML::Node& node) const -> void {
    // Geometry
    ExportValue(node, fLength, "Length");
    ExportValue(node, fInnerRadius, "InnerRadius");
    ExportValue(node, fBerylliumLength, "BerylliumLength");
    ExportValue(node, fBerylliumThickness, "BerylliumThickness");
    ExportValue(node, fAluminiumThickness, "AluminiumThickness");
    // Material
    ExportValue(node, fVacuumPressure, "VacuumPressure");
}

} // namespace MACE::PhaseI::Detector::Description
