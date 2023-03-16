#pragma once

#include "MACE/Env/BasicEnv.hxx"
#include "MACE/Env/Memory/Singleton.hxx"
#include "MACE/Env/Memory/Singletonized.hxx"
#include "MACE/Utility/NonMoveableBase.hxx"
#include "MACE/Utility/TupleForEach.hxx"

#include "yaml-cpp/yaml.h"

#include "gsl/gsl"

#include <array>
#include <concepts>
#include <iostream>
#include <optional>
#include <string>

namespace MACE::Detector {

class DescriptionBase : public NonMoveableBase {
protected:
    DescriptionBase(const std::string& name);
    ~DescriptionBase() = default;

public:
    const auto& GetName() const { return fName; }

    void Import(const YAML::Node& rootNode);
    void Export(YAML::Node& rootNode) const;

protected:
    template<typename AValue, typename AReadAs = AValue, std::convertible_to<std::string>... AStrings>
        requires std::assignable_from<AValue&, AReadAs>
    void ImportValue(const YAML::Node& node, AValue& value, AStrings&&... nodeNames);
    template<typename AReadAs, std::convertible_to<std::string>... AStrings>
    void ImportValue(const YAML::Node& node, const std::regular_invocable<AReadAs> auto& ImportAction, AStrings&&... nodeNames);
    template<typename AValue, typename AWriteAs = AValue, std::convertible_to<std::string>... AStrings>
        requires std::convertible_to<const AValue&, AWriteAs>
    void ExportValue(YAML::Node& node, const AValue& value, AStrings&&... nodeNames) const;

private:
    virtual void ImportValues(const YAML::Node& node) = 0;
    virtual void ExportValues(YAML::Node& node) const = 0;

    template<std::convertible_to<std::string>... AStrings>
    std::optional<const YAML::Node> UnpackToLeafNodeForImporting(const YAML::Node& node, AStrings&&... nodeNames);
    template<std::convertible_to<std::string>... AStrings>
    YAML::Node UnpackToLeafNodeForExporting(YAML::Node& node, AStrings&&... nodeNames) const;
    template<std::convertible_to<std::string>... AStrings>
    void PrintNodeNotFoundWarning(AStrings&&... nodeNames) const;

private:
    std::string fName;
};

template<class ADerived>
class DescriptionSingletonBase : public Env::Memory::Singleton<ADerived>,
                                 public DescriptionBase {
protected:
    using DescriptionBase::DescriptionBase;
};

template<class T>
concept IsDescription =
    requires {
        requires std::derived_from<T, DescriptionBase>;
        requires std::derived_from<T, DescriptionSingletonBase<T>>;
        requires Env::Memory::Singletonized<T>;
    };

} // namespace MACE::Geometry

#include "MACE/Detector/DescriptionBase.inl"
