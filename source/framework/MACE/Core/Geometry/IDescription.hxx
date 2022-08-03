#pragma once

#include "MACE/Environment/Memory/Concept/Singletonized.hxx"
#include "MACE/Environment/Memory/Singleton.hxx"

#include "yaml-cpp/yaml.h"

#include <concepts>
#include <iostream>
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

    void Read(const YAML::Node& geomYaml);
    void Write(YAML::Node& geomYaml) const;

protected:
    template<typename AValue, typename AReadAs = AValue> // clang-format off
        requires std::assignable_from<AValue&, AReadAs>
    void ReadValueNode(const YAML::Node& node, const std::string& valueName, AValue& value); // clang-format on
    template<typename AReadAs>
    void ReadValueNode(const YAML::Node& node, const std::string& valueName, const std::regular_invocable<AReadAs> auto& ReadAction);
    template<typename AValue, typename AWriteAs = AValue> // clang-format off
        requires std::convertible_to<const AValue&, AWriteAs>
    void WriteValueNode(YAML::Node& node, const std::string& valueName, const AValue& value) const { node[valueName] = static_cast<AWriteAs>(value); } // clang-format on

private:
    virtual void ReadDescriptionNode(const YAML::Node& node) = 0;
    virtual void WriteDescriptionNode(YAML::Node& node) const = 0;

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
    requires Environment::Memory::Concept::Singletonized<T>;
};

} // namespace MACE::Core::Geometry

#include "MACE/Core/Geometry/IDescription.inl"
