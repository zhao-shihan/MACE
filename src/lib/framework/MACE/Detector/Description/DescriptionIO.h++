#pragma once

#include "MACE/Detector/Description/DescriptionBase.h++"
#include "MACE/Env/MPIEnv.h++"
#include "MACE/Extension/stdx/tuple_like.h++"
#include "MACE/Utility/MPIUtil/MakeMPIFilePath.h++"
#include "MACE/Utility/NonConstructibleBase.h++"
#include "MACE/Utility/StaticForEach.h++"

#include "yaml-cpp/yaml.h"

#include "gsl/gsl"

#include "fmt/format.h"

#include <algorithm>
#include <array>
#include <chrono>
#include <concepts>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <ranges>
#include <set>
#include <stdexcept>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <vector>

namespace MACE::Detector::Description {

class DescriptionIO final : public NonConstructibleBase {
public:
    template<Description... Ds>
    static void Import(const std::filesystem::path& yamlFile) { Import<std::tuple<Ds...>>(yamlFile); }
    template<Description... Ds>
    static void Export(const std::filesystem::path& yamlFile, std::string_view fileComment = "") { Export<std::tuple<Ds...>>(yamlFile, fileComment); }
    template<Description... Ds>
    static void Ixport(const std::filesystem::path& yamlFile, std::string_view fileComment = "") { Ixport<std::tuple<Ds...>>(yamlFile, fileComment); }
    template<stdx::tuple_like T>
    static void Import(const std::filesystem::path& yamlFile);
    template<stdx::tuple_like T>
    static void Export(const std::filesystem::path& yamlFile, std::string_view fileComment = "");
    template<stdx::tuple_like T>
    static void Ixport(const std::filesystem::path& yamlFile, std::string_view fileComment = "");

    template<typename... ArgsOfImport>
    static void Import(const std::ranges::range auto& yamlText)
        requires std::convertible_to<typename std::decay_t<decltype(yamlText)>::value_type, std::string>;

    static void AddInstance(gsl::not_null<DescriptionBase*> instance) { fgInstanceSet.emplace(instance); }
    static void ImportInstantiated(const std::filesystem::path& yamlFile) { ImportImpl(yamlFile, fgInstanceSet); }
    static void ExportInstantiated(const std::filesystem::path& yamlFile, std::string_view fileComment = "") { ExportImpl(yamlFile, fileComment, fgInstanceSet); }

private:
    static void ImportImpl(const std::filesystem::path& yamlFile, std::ranges::input_range auto& descriptions);
    static void ExportImpl(const std::filesystem::path& yamlFile, std::string_view fileComment, const std::ranges::input_range auto& descriptions);
    static void IxportImpl(const std::filesystem::path& yamlFile, std::string_view fileComment, const std::ranges::input_range auto& descriptions);

private:
    static std::set<gsl::not_null<DescriptionBase*>> fgInstanceSet;
};

} // namespace MACE::Detector::Description

#include "MACE/Detector/Description/DescriptionIO.inl"
