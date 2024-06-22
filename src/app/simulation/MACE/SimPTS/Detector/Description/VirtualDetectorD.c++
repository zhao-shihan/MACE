#include "MACE/SimPTS/Detector/Description/VirtualDetectorD.h++"

#include "Mustard/Utility/LiteralUnit.h++"

namespace MACE::SimPTS::Detector::Description {

using namespace Mustard::LiteralUnit::Length;

VirtualDetectorD::VirtualDetectorD() :
    DescriptionBase{"VirtualDetectorD"},
    fThickness{1_nm} {}

void VirtualDetectorD::ImportAllValue(const YAML::Node& node) {
    ImportValue(node, fThickness, "Thickness");
}

void VirtualDetectorD::ExportAllValue(YAML::Node& node) const {
    ExportValue(node, fThickness, "Thickness");
}

} // namespace MACE::SimPTS::Detector::Description
