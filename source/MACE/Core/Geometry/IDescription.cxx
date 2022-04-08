#include "MACE/Core/Geometry/IDescription.hxx"

using MACE::Core::Geometry::IDescription;

IDescription::IDescription(const std::string& name) :
    fName(name) {}

void IDescription::Read(const YAML::Node& geomYaml) {
    const auto thisNode = geomYaml[fName];
    ReadImpl(thisNode);
}

void IDescription::Write(YAML::Node& geomYaml) const {
    auto thisNode = geomYaml[fName];
    WriteImpl(thisNode);
}
