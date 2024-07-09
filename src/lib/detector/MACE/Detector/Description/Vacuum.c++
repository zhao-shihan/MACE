#include "MACE/Detector/Description/Vacuum.h++"

#include "Mustard/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace Mustard::LiteralUnit::Pressure;

Vacuum::Vacuum() :
    DescriptionBase{"Vacuum"},
    fName{"MACE_Vacuum"},
    fPressure{1e-4_Pa} {}

auto Vacuum::Density() const -> double {
    using namespace Mustard::LiteralUnit::Density;
    return fPressure / 1_atm * 1.177_kg_m3;
}

auto Vacuum::ImportAllValue(const YAML::Node& node) -> void {
    ImportValue(node, fName, "Name");
    ImportValue(node, fPressure, "Pressure");
}

auto Vacuum::ExportAllValue(YAML::Node& node) const -> void {
    ExportValue(node, fName, "Name");
    ExportValue(node, fPressure, "Pressure");
}

} // namespace MACE::Detector::Description
