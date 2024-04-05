#pragma once

#include "MACE/Detector/Description/Description.h++"
#include "MACE/Env/BasicEnv.h++"
#include "MACE/Env/Memory/Singleton.h++"
#include "MACE/Env/Memory/Singletonified.h++"
#include "MACE/Env/Print.h++"
#include "MACE/Utility/NonMoveableBase.h++"

#include "yaml-cpp/yaml.h"

#include "gsl/gsl"

#include <array>
#include <concepts>
#include <iostream>
#include <optional>
#include <string>
#include <utility>

namespace MACE::Detector::Description {

template<typename... Ts>
    requires(sizeof...(Ts) <= 1)
class DescriptionBase;

template<>
class DescriptionBase<> : public NonMoveableBase {
protected:
    DescriptionBase(std::string name);
    ~DescriptionBase() = default;

public:
    const auto& Name() const { return fName; }

    auto Import(const YAML::Node& rootNode) -> void;
    auto Export(YAML::Node& rootNode) const -> void;

protected:
    template<typename AValue, typename AReadAs = AValue, std::convertible_to<std::string>... AStrings>
        requires std::assignable_from<AValue&, AReadAs>
    auto ImportValue(const YAML::Node& node, AValue& value, AStrings&&... nodeNames) -> void;
    template<typename AReadAs, std::convertible_to<std::string>... AStrings>
    auto ImportValue(const YAML::Node& node, const std::regular_invocable<AReadAs> auto& ImportAction, AStrings&&... nodeNames) -> void;
    template<typename AValue, typename AWriteAs = AValue, std::convertible_to<std::string>... AStrings>
        requires std::convertible_to<const AValue&, AWriteAs>
    auto ExportValue(YAML::Node& node, const AValue& value, AStrings&&... nodeNames) const -> void;

private:
    virtual void ImportAllValue(const YAML::Node& node) = 0;
    virtual void ExportAllValue(YAML::Node& node) const = 0;

    template<std::convertible_to<std::string>... AStrings>
    auto UnpackToLeafNodeForImporting(const YAML::Node& node, AStrings&&... nodeNames) -> std::optional<const YAML::Node>;
    template<std::convertible_to<std::string>... AStrings>
    auto UnpackToLeafNodeForExporting(YAML::Node& node, AStrings&&... nodeNames) const -> YAML::Node;
    template<std::convertible_to<std::string>... AStrings>
    auto PrintNodeNotFoundWarning(AStrings&&... nodeNames) const -> void;

private:
    std::string fName;
};

template<typename ADerived>
class DescriptionBase<ADerived> : public Env::Memory::Singleton<ADerived>,
                                  public DescriptionBase<> {
protected:
    DescriptionBase(std::string name);
    ~DescriptionBase() = default;
};

} // namespace MACE::Detector::Description

#include "MACE/Detector/Description/DescriptionBase.inl"
