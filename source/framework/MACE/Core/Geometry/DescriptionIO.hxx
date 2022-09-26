#pragma once

#include "MACE/Concept/InstantiatedFrom.hxx"
#include "MACE/Core/Geometry/IDescription.hxx"
#include "MACE/Environment/MPIEnvironment.hxx"
#include "MACE/Utility/MPIUtil/MakeMPIFilePath.hxx"
#include "MACE/Utility/ObserverPtr.hxx"
#include "MACE/Utility/StaticForEach.hxx"

#include "yaml-cpp/yaml.h"

#include <algorithm>
#include <array>
#include <chrono>
#include <concepts>
#include <filesystem>
#include <fstream>
#include <ranges>
#include <set>
#include <stdexcept>
#include <string>
#include <string_view>
#include <tuple>
#include <vector>

namespace MACE::Core::Geometry {

using Utility::ObserverPtr;

class DescriptionIO final {
public:
    DescriptionIO() = delete;

    template<IsDescription... ADescriptions>
    static void Import(const std::filesystem::path& yamlFile) { Import<std::tuple<ADescriptions...>>(yamlFile); }
    template<IsDescription... ADescriptions>
    static void Export(const std::filesystem::path& yamlFile, const std::string& fileComment = "") { Export<std::tuple<ADescriptions...>>(yamlFile, fileComment); }
    template<IsDescription... ADescriptions>
    static void Ixport(const std::filesystem::path& yamlFile, const std::string& fileComment = "") { Ixport<std::tuple<ADescriptions...>>(yamlFile, fileComment); }
    template<Concept::InstantiatedFrom<std::tuple> ADescriptionTuple>
    static void Import(const std::filesystem::path& yamlFile) requires(not IsDescription<ADescriptionTuple>);
    template<Concept::InstantiatedFrom<std::tuple> ADescriptionTuple>
    static void Export(const std::filesystem::path& yamlFile, const std::string& fileComment = "") requires(not IsDescription<ADescriptionTuple>);
    template<Concept::InstantiatedFrom<std::tuple> ADescriptionTuple>
    static void Ixport(const std::filesystem::path& yamlFile, const std::string& fileComment = "") requires(not IsDescription<ADescriptionTuple>);

    template<typename... ArgsOfImport>
    static void Import(const std::ranges::range auto& yamlText) requires
        std::convertible_to<typename std::remove_cvref_t<decltype(yamlText)>::value_type, std::string>;

    static void AddInstance(IDescription& instance) { fgInstanceSet.emplace(std::addressof(instance)); }
    static void ImportInstantiated(const std::filesystem::path& yamlFile) { ImportImpl(yamlFile, fgInstanceSet); }
    static void ExportInstantiated(const std::filesystem::path& yamlFile, const std::string& fileComment = "") { ExportImpl(yamlFile, fileComment, fgInstanceSet); }

private:
    static void ImportImpl(const std::filesystem::path& yamlFile, std::ranges::range auto& descriptions);
    static void ExportImpl(const std::filesystem::path& yamlFile, std::string fileComment, const std::ranges::range auto& descriptions);
    static void IxportImpl(const std::filesystem::path& yamlFile, std::string fileComment, const std::ranges::range auto& descriptions);

private:
    static std::set<ObserverPtr<IDescription>> fgInstanceSet;
};

} // namespace MACE::Core::Geometry

#include "MACE/Core/Geometry/DescriptionIO.inl"
