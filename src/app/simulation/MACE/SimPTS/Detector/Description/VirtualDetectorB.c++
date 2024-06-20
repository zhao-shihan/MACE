#include "MACE/SimPTS/Detector/Description/VirtualDetectorB.h++"

#include "Mustard/Utility/LiteralUnit.h++"

namespace MACE::SimPTS::Detector::Description {

using namespace Mustard::LiteralUnit::Length;

VirtualDetectorB::VirtualDetectorB() :
    DescriptionBase{"VirtualDetectorB"},
    fThickness{1_nm} {}

void VirtualDetectorB::ImportAllValue(const YAML::Node& node) {
    ImportValue(node, fThickness, "Thickness");
}

void VirtualDetectorB::ExportAllValue(YAML::Node& node) const {
    ExportValue(node, fThickness, "Thickness");
}

} // namespace MACE::SimPTS::Detector::Description
