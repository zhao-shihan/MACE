#include "MACE/Core/Geometry/DescriptionIO.hxx"
#include "MACE/Core/Geometry/IDescription.hxx"

namespace MACE::Core::Geometry {

IDescription::IDescription(const std::string& name) :
    fName(name) {
    DescriptionIO::AddInstance(*this);
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

} // namespace MACE::Core::Geometry
