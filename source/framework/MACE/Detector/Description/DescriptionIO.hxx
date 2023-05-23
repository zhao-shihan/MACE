#pragma once

#include "MACE/Concept/InstantiatedFrom.hxx"
#include "MACE/Detector/Description/DescriptionBase.hxx"
#include "MACE/Env/MPIEnv.hxx"
#include "MACE/Utility/MPIUtil/MakeMPIFilePath.hxx"
#include "MACE/Utility/NonConstructibleBase.hxx"
#include "MACE/Utility/StaticForEach.hxx"

#include "yaml-cpp/yaml.h"

#include "gsl/gsl"

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

namespace MACE::Detector::Description {

using namespace std::string_view_literals;

class DescriptionIO final : public NonConstructibleBase {
public:
    template<Description... Ds>
    static void Import(const std::filesystem::path& yamlFile) { Import<std::tuple<Ds...>>(yamlFile); }
    template<Description... Ds>
    static void Export(const std::filesystem::path& yamlFile, std::string_view fileComment = ""sv) { Export<std::tuple<Ds...>>(yamlFile, fileComment); }
    template<Description... Ds>
    static void Ixport(const std::filesystem::path& yamlFile, std::string_view fileComment = ""sv) { Ixport<std::tuple<Ds...>>(yamlFile, fileComment); }
    template<Concept::InstantiatedFrom<std::tuple> T>
    static void Import(const std::filesystem::path& yamlFile)
        requires(not Description<T>);
    template<Concept::InstantiatedFrom<std::tuple> T>
    static void Export(const std::filesystem::path& yamlFile, std::string_view fileComment = ""sv)
        requires(not Description<T>);
    template<Concept::InstantiatedFrom<std::tuple> T>
    static void Ixport(const std::filesystem::path& yamlFile, std::string_view fileComment = ""sv)
        requires(not Description<T>);

    template<typename... ArgsOfImport>
    static void Import(const std::ranges::range auto& yamlText)
        requires std::convertible_to<typename std::remove_cvref_t<decltype(yamlText)>::value_type, std::string>;

    static void AddInstance(gsl::not_null<DescriptionBase*> instance) { fgInstanceSet.emplace(instance); }
    static void ImportInstantiated(const std::filesystem::path& yamlFile) { ImportImpl(yamlFile, fgInstanceSet); }
    static void ExportInstantiated(const std::filesystem::path& yamlFile, std::string_view fileComment = ""sv) { ExportImpl(yamlFile, fileComment, fgInstanceSet); }

private:
    static void ImportImpl(const std::filesystem::path& yamlFile, std::ranges::input_range auto& descriptions);
    static void ExportImpl(const std::filesystem::path& yamlFile, std::string_view fileComment, const std::ranges::input_range auto& descriptions);
    static void IxportImpl(const std::filesystem::path& yamlFile, std::string_view fileComment, const std::ranges::input_range auto& descriptions);

private:
    static std::set<gsl::not_null<DescriptionBase*>> fgInstanceSet;
};

} // namespace MACE::Detector

#include "MACE/Detector/Description/DescriptionIO.inl"
