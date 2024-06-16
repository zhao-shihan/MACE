#include "MACE/Detector/Description/FieldOption.h++"

#include "Mustard/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace Mustard::LiteralUnit::Length;

FieldOption::FieldOption() :
    DescriptionBase{"FieldOption"},
    fUseFast{false},
    fFieldDataFileName{"${MACE_FIELD_DATA}"} {}

auto FieldOption::ImportAllValue(const YAML::Node& node) -> void {
    ImportValue(node, fUseFast, "UseFast");
    ImportValue(node, fFieldDataFileName, "FieldDataFileName");
}

auto FieldOption::ExportAllValue(YAML::Node& node) const -> void {
    ExportValue(node, fUseFast, "UseFast");
    ExportValue(node, fFieldDataFileName, "FieldDataFileName");
}

} // namespace MACE::Detector::Description
