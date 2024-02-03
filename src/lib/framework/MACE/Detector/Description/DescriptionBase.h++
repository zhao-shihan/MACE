#pragma once

#include "MACE/Env/BasicEnv.h++"
#include "MACE/Env/Memory/Singleton.h++"
#include "MACE/Env/Memory/Singletonified.h++"
#include "MACE/Utility/NonMoveableBase.h++"

#include "yaml-cpp/yaml.h"

#include "gsl/gsl"

#include <array>
#include <concepts>
#include <iostream>
#include <optional>
#include <string>

namespace MACE::Detector::Description {

class DescriptionBase : public NonMoveableBase {
protected:
    DescriptionBase(const std::string& name);
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
    virtual void ImportValues(const YAML::Node& node) = 0;
    virtual void ExportValues(YAML::Node& node) const = 0;

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
class DescriptionSingletonBase : public Env::Memory::Singleton<ADerived>,
                                 public DescriptionBase {
protected:
    using DescriptionBase::DescriptionBase;
};

template<typename T>
concept Description =
    requires {
        requires std::derived_from<T, DescriptionBase>;
        requires std::derived_from<T, DescriptionSingletonBase<T>>;
        requires Env::Memory::Singletonified<T>;
    };

} // namespace MACE::Detector::Description

#include "MACE/Detector/Description/DescriptionBase.inl"
