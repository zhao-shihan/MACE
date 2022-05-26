#pragma once

#include "MACE/Utility/ObserverPtr.hxx"

#include <vector>
#include <string>

namespace MACE::Core::Geometry {

using MACE::Utility::ObserverPtr;

class IDescription;

class DescriptionIO {
    friend class IDescription;

public:
    DescriptionIO() = delete;

    static void ReadInstantiated(const std::string& yamlFileName);
    static void WriteInstantiated(const std::string& yamlFileName);

private:
    static void AddInstance(ObserverPtr<IDescription> instance);

private:
    static std::vector<ObserverPtr<IDescription>> fgInstantiatedDescriptionList;
};

} // namespace MACE::Core::Geometry
