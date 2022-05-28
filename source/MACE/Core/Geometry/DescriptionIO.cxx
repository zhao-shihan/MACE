#include "MACE/Core/Geometry/DescriptionIO.hxx"
#include "MACE/Core/Geometry/IDescription.hxx"

#include "yaml-cpp/yaml.h"

#include <fstream>

namespace MACE::Core::Geometry {

std::vector<ObserverPtr<IDescription>> DescriptionIO::fgInstantiatedDescriptionList;

void DescriptionIO::ReadInstantiated(const std::string& yamlFileName) {
    const auto geomYaml = YAML::LoadFile(yamlFileName);
    for (auto&& description : std::as_const(fgInstantiatedDescriptionList)) {
        description->Read(geomYaml);
    }
}

void DescriptionIO::WriteInstantiated(const std::string& yamlFileName) {
    YAML::Node geomYaml;
    for (auto&& description : std::as_const(fgInstantiatedDescriptionList)) {
        description->Write(geomYaml);
    }
    std::ofstream yamlOut(yamlFileName, std::ios::out);
    yamlOut << geomYaml;
    yamlOut.close();
}

void DescriptionIO::AddInstance(ObserverPtr<IDescription> instance) {
    fgInstantiatedDescriptionList.emplace_back(instance);
}

} // namespace MACE::Core::Geometry
