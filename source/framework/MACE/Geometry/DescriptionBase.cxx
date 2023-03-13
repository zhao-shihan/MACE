#include "MACE/Geometry/DescriptionBase.hxx"
#include "MACE/Geometry/DescriptionIO.hxx"

namespace MACE::Geometry {

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

} // namespace MACE::Geometry
