#pragma once

#include "MACE/Environment/BasicEnvironment.hxx"
#include "MACE/Environment/Memory/Singletonized.hxx"
#include "MACE/Environment/Memory/Singleton.hxx"
#include "MACE/Utility/TupleForEach.hxx"

#include "yaml-cpp/yaml.h"

#include <array>
#include <concepts>
#include <iostream>
#include <optional>
#include <string>

namespace MACE::Core::Geometry {

class IDescription {
protected:
    IDescription(const std::string& name);
    ~IDescription() = default;
    IDescription(const IDescription&) = delete;
    IDescription& operator=(const IDescription&) = delete;

public:
    const auto& GetName() const { return fName; }

    void Import(const YAML::Node& rootNode);
    void Export(YAML::Node& rootNode) const;

protected:
    template<typename AValue, typename AReadAs = AValue, std::convertible_to<std::string>... AStrings> // clang-format off
        requires std::assignable_from<AValue&, AReadAs>
    void ImportValue(const YAML::Node& node, AValue& value, AStrings&&... nodeNames); // clang-format on
    template<typename AReadAs, std::convertible_to<std::string>... AStrings>
    void ImportValue(const YAML::Node& node, const std::regular_invocable<AReadAs> auto& ImportAction, AStrings&&... nodeNames);
    template<typename AValue, typename AWriteAs = AValue, std::convertible_to<std::string>... AStrings> // clang-format off
        requires std::convertible_to<const AValue&, AWriteAs>
    void ExportValue(YAML::Node& node, const AValue& value, AStrings&&... nodeNames) const; // clang-format on

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
class ISingletonDescription : public Environment::Memory::Singleton<ADerived>,
                              public IDescription {
protected:
    using IDescription::IDescription;
};

template<class T>
concept IsDescription = requires {
    requires std::derived_from<T, IDescription>;
    requires std::derived_from<T, ISingletonDescription<T>>;
    requires Environment::Memory::Singletonized<T>;
};

} // namespace MACE::Core::Geometry

#include "MACE/Core/Geometry/IDescription.inl"
