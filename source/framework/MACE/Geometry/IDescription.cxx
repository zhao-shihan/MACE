#include "MACE/Geometry/DescriptionIO.hxx"
#include "MACE/Geometry/IDescription.hxx"

namespace MACE::Geometry {

IDescription::IDescription(const std::string& name) :
    NonMoveableBase(),
    fName(name) {
    DescriptionIO::AddInstance(this);
}

void IDescription::Import(const YAML::Node& rootNode) {
    const auto node = rootNode[fName];
    if (node.IsDefined()) {
        ImportValues(node);
    } else {
        PrintNodeNotFoundWarning();
    }
}

void IDescription::Export(YAML::Node& rootNode) const {
    auto node = rootNode[fName];
    ExportValues(node);
}

} // namespace MACE::Geometry
