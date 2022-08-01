#pragma once

#include <functional>
#include <string>
#include <vector>

namespace MACE::Core::Geometry {

class IDescription;

class DescriptionIO final {
    friend class IDescription;

public:
    DescriptionIO() = delete;

    static void ReadInstantiated(const std::string& yamlFileName);
    static void WriteInstantiated(const std::string& yamlFileName);

private:
    static void AddInstance(IDescription& instance);

private:
    static std::vector<std::reference_wrapper<IDescription>> fgInstantiatedDescriptionList;
};

} // namespace MACE::Core::Geometry
