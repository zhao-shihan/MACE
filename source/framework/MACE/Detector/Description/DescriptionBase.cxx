#include "MACE/Detector/Description/DescriptionBase.hxx"
#include "MACE/Detector/Description/DescriptionIO.hxx"

namespace MACE::Detector::Description {

DescriptionBase::DescriptionBase(const std::string& name) :
    NonMoveableBase(),
    fName(name) {
    DescriptionIO::AddInstance(this);
}

void DescriptionBase::Import(const YAML::Node& rootNode) {
    const auto node = rootNode[fName];
    if (node.IsDefined()) {
        ImportValues(node);
    } else {
        PrintNodeNotFoundWarning();
    }
}

void DescriptionBase::Export(YAML::Node& rootNode) const {
    auto node = rootNode[fName];
    ExportValues(node);
}

} // namespace MACE::Detector
