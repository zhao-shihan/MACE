#include "MACE/PhaseI/Detector/Description/MRPC.h++"

#include "Mustard/Utility/LiteralUnit.h++"

namespace MACE::PhaseI::Detector::Description {

using namespace Mustard::LiteralUnit::Length;

MRPC::MRPC() :
    DescriptionBase{"MRPC"},
    fHoneyCombThickness{4_mm},
    fPCBThickness{1.5_mm},
    fMylarThickness{0.35_mm},
    fAnodeThickness{0.13_mm},
    fOuterGlassThickness{0.7_mm},
    fInnerGlassThickness{0.54_mm},
    fNGaps{6},
    fGasGapThickness{0.22_mm},
    fGasTankThickness{1.5_mm},
    fNMRPCs{8},
    fCentralRadius{6.35_cm},
    fCentralMRPCLength{35_cm},
    fCentralMRPCWidth{10_cm},
    fCornerRadius{11.6_cm},
    fCornerMRPCLength{35_cm},
    fCornerMRPCWidth{10_cm} {}

auto MRPC::ImportAllValue(const YAML::Node& node) -> void {
    // Geometry
    ImportValue(node, fHoneyCombThickness, "HoneyCombThickness");
    ImportValue(node, fPCBThickness, "PCBThickness");
    ImportValue(node, fMylarThickness, "MylarThickness");
    ImportValue(node, fAnodeThickness, "AnodeThickness");
    ImportValue(node, fOuterGlassThickness, "OuterGlassThickness");
    ImportValue(node, fInnerGlassThickness, "InnerGlassThickness");
    ImportValue(node, fNGaps, "NGaps");
    ImportValue(node, fGasGapThickness, "GasGapThickness");
    ImportValue(node, fGasTankThickness, "GasTankThickness");
    ImportValue(node, fNMRPCs, "NMRPCs");
    ImportValue(node, fCentralRadius, "CentralRadius");
    ImportValue(node, fCentralMRPCLength, "CentralMRPCLength");
    ImportValue(node, fCentralMRPCWidth, "CentralMRPCWidth");
    ImportValue(node, fCornerRadius, "CornerRadius");
    ImportValue(node, fCornerMRPCLength, "CornerMRPCLength");
    ImportValue(node, fCornerMRPCWidth, "CornerMRPCWidth");
}

auto MRPC::ExportAllValue(YAML::Node& node) const -> void {
    // Geometry
    ExportValue(node, fHoneyCombThickness, "HoneyCombThickness");
    ExportValue(node, fPCBThickness, "PCBThickness");
    ExportValue(node, fMylarThickness, "MylarThickness");
    ExportValue(node, fAnodeThickness, "AnodeThickness");
    ExportValue(node, fOuterGlassThickness, "OuterGlassThickness");
    ExportValue(node, fInnerGlassThickness, "InnerGlassThickness");
    ExportValue(node, fNGaps, "NGaps");
    ExportValue(node, fGasGapThickness, "GasGapThickness");
    ExportValue(node, fGasTankThickness, "GasTankThickness");
    ExportValue(node, fNMRPCs, "NMRPCs");
    ExportValue(node, fCentralRadius, "CentralRadius");
    ExportValue(node, fCentralMRPCLength, "CentralMRPCLength");
    ExportValue(node, fCentralMRPCWidth, "CentralMRPCWidth");
    ExportValue(node, fCornerRadius, "CornerRadius");
    ExportValue(node, fCornerMRPCLength, "CornerMRPCLength");
    ExportValue(node, fCornerMRPCWidth, "CornerMRPCWidth");
}

} // namespace MACE::PhaseI::Detector::Description
