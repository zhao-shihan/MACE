#include "MACE/SimPTS/Detector/Description/VirtualDetectorC.h++"

#include "Mustard/Utility/LiteralUnit.h++"

namespace MACE::SimPTS::Detector::Description {

using namespace Mustard::LiteralUnit::Length;

VirtualDetectorC::VirtualDetectorC() :
    DescriptionBase{"VirtualDetectorC"},
    fThickness{1_nm} {}

void VirtualDetectorC::ImportAllValue(const YAML::Node& node) {
    ImportValue(node, fThickness, "Thickness");
}

void VirtualDetectorC::ExportAllValue(YAML::Node& node) const {
    ExportValue(node, fThickness, "Thickness");
}

} // namespace MACE::SimPTS::Detector::Description
