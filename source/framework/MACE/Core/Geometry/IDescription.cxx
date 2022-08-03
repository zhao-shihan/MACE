#include "MACE/Core/Geometry/DescriptionIO.hxx"
#include "MACE/Core/Geometry/IDescription.hxx"

namespace MACE::Core::Geometry {

IDescription::IDescription(const std::string& name) :
    fName(name) {
    DescriptionIO::AddInstance(*this);
}

void IDescription::Read(const YAML::Node& geomYaml) {
    const auto thisNode = geomYaml[fName];
    if (geomYaml.IsDefined()) {
        ReadDescriptionNode(thisNode);
    } else {
        std::cout << "Node <" << fName << "> not defined, skipping." << std::endl;
    }
}

void IDescription::Write(YAML::Node& geomYaml) const {
    auto nodeForThis = geomYaml[fName];
    WriteDescriptionNode(nodeForThis);
}

} // namespace MACE::Core::Geometry
