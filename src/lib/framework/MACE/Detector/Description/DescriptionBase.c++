#include "MACE/Detector/Description/DescriptionBase.h++"
#include "MACE/Detector/Description/DescriptionIO.h++"

namespace MACE::Detector::Description {

DescriptionBase<>::DescriptionBase(std::string name) :
    NonMoveableBase{},
    fName{std::move(name)} {
    DescriptionIO::AddInstance(this);
}

auto DescriptionBase<>::Import(const YAML::Node& rootNode) -> void {
    const auto node{rootNode[fName]};
    if (node.IsDefined()) {
        ImportAllValue(node);
    } else {
        PrintNodeNotFoundWarning();
    }
}

auto DescriptionBase<>::Export(YAML::Node& rootNode) const -> void {
    auto node{rootNode[fName]};
    ExportAllValue(node);
}

} // namespace MACE::Detector::Description
