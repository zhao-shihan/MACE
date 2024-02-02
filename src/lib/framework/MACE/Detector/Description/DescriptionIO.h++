#pragma once

#include "MACE/Detector/Description/DescriptionBase.h++"
#include "MACE/Env/MPIEnv.h++"
#include "MACE/Extension/MPIX/ParallelizePath.h++"
#include "MACE/Extension/stdx/tuple_like.h++"
#include "MACE/Utility/NonConstructibleBase.h++"

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
    static auto Import(const std::filesystem::path& yamlFile) -> void { Import<std::tuple<Ds...>>(yamlFile); }
    template<Description... Ds>
    static auto Export(const std::filesystem::path& yamlFile, std::string_view fileComment = {}) -> void { Export<std::tuple<Ds...>>(yamlFile, fileComment); }
    template<Description... Ds>
    static auto Ixport(const std::filesystem::path& yamlFile, std::string_view fileComment = {}) -> void { Ixport<std::tuple<Ds...>>(yamlFile, fileComment); }
    template<stdx::tuple_like T>
    static auto Import(const std::filesystem::path& yamlFile) -> void;
    template<stdx::tuple_like T>
    static auto Export(const std::filesystem::path& yamlFile, std::string_view fileComment = {}) -> void;
    template<stdx::tuple_like T>
    static auto Ixport(const std::filesystem::path& yamlFile, std::string_view fileComment = {}) -> void;

    template<typename... ArgsOfImport>
    static auto Import(const std::ranges::range auto& yamlText) -> void
        requires std::convertible_to<typename std::decay_t<decltype(yamlText)>::value_type, std::string>;

    static auto AddInstance(gsl::not_null<DescriptionBase*> instance) -> void { fgInstanceSet.emplace(instance); }
    static auto ImportInstantiated(const std::filesystem::path& yamlFile) -> void { ImportImpl(yamlFile, fgInstanceSet); }
    static auto ExportInstantiated(const std::filesystem::path& yamlFile, std::string_view fileComment = {}) -> void { ExportImpl(yamlFile, fileComment, fgInstanceSet); }

private:
    static auto ImportImpl(const std::filesystem::path& yamlFile, std::ranges::input_range auto& descriptions) -> void;
    static auto ExportImpl(const std::filesystem::path& yamlFile, std::string_view fileComment, const std::ranges::input_range auto& descriptions) -> void;
    static auto IxportImpl(const std::filesystem::path& yamlFile, std::string_view fileComment, const std::ranges::input_range auto& descriptions) -> void;

private:
    static std::set<gsl::not_null<DescriptionBase*>> fgInstanceSet;
};

} // namespace MACE::Detector::Description

#include "MACE/Detector/Description/DescriptionIO.inl"
