#include "MACE/SimPTS/Detector/Description/VirtualDetectorA.h++"

#include "Mustard/Utility/LiteralUnit.h++"

namespace MACE::SimPTS::Detector::Description {

using namespace Mustard::LiteralUnit::Length;

VirtualDetectorA::VirtualDetectorA() :
    DescriptionBase{"VirtualDetectorA"},
    fThickness{1_nm} {}

void VirtualDetectorA::ImportAllValue(const YAML::Node& node) {
    ImportValue(node, fThickness, "Thickness");
}

void VirtualDetectorA::ExportAllValue(YAML::Node& node) const {
    ExportValue(node, fThickness, "Thickness");
}

} // namespace MACE::SimPTS::Detector::Description
