#pragma once

#include "MACE/Core/Geometry/IDescription.hxx"
#include "MACE/Utility/Concept/InstantiatedFrom.hxx"
#include "MACE/Utility/ObserverPtr.hxx"
#include "MACE/Utility/StaticForEach.hxx"

#include "yaml-cpp/yaml.h"

#include <algorithm>
#include <fstream>
#include <ranges>
#include <set>
#include <string>
#include <string_view>
#include <tuple>

namespace MACE::Core::Geometry {

using Utility::ObserverPtr;
using Utility::Concept::InstantiatedFrom;

class DescriptionIO final {
public:
    DescriptionIO() = delete;

    template<IsDescription... ADescriptions>
    static void Import(const std::string& yamlFileName) { Import<std::tuple<ADescriptions...>>(yamlFileName); }
    template<IsDescription... ADescriptions>
    static void Export(const std::string& yamlFileName, const std::string& fileComment = "") { Export<std::tuple<ADescriptions...>>(yamlFileName, fileComment); }
    template<InstantiatedFrom<std::tuple> ADescriptionTuple>
    static void Import(const std::string& yamlFileName);
    template<InstantiatedFrom<std::tuple> ADescriptionTuple>
    static void Export(const std::string& yamlFileName, const std::string& fileComment = "");

    static void AddInstance(IDescription& instance) { fgInstanceSet.emplace(std::addressof(instance)); }
    static void ImportInstantiated(const std::string& yamlFileName) { ImportImpl(yamlFileName, fgInstanceSet); }
    static void ExportInstantiated(const std::string& yamlFileName, const std::string& fileComment = "") { ExportImpl(yamlFileName, fileComment, fgInstanceSet); }

private:
    static void ImportImpl(const std::string& yamlFileName, std::ranges::range auto& descriptions);
    static void ExportImpl(const std::string& yamlFileName, std::string fileComment, const std::ranges::sized_range auto& descriptions);

private:
    static std::set<ObserverPtr<IDescription>> fgInstanceSet;
};

} // namespace MACE::Core::Geometry

#include "MACE/Core/Geometry/DescriptionIO.inl"
