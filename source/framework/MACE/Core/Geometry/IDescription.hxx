#pragma once

#include "MACE/Environment/Resource/Singleton.hxx"

#include "yaml-cpp/yaml.h"

#include <string>

namespace MACE::Core::Geometry {

class IDescription {
protected:
    IDescription(const std::string& name);
    virtual ~IDescription() noexcept = default;
    IDescription(const IDescription&) = delete;
    IDescription& operator=(const IDescription&) = delete;

public:
    const auto& GetName() const { return fName; }

    void Read(const YAML::Node& geomYaml);
    void Write(YAML::Node& geomYaml) const;

protected:
    template<typename AValue, typename AReadAs = AValue>
    void ReadValueNode(const YAML::Node& node, const char* valueName, AValue& value);
    template<typename AValue, typename AWriteAs = AValue>
    void WriteValueNode(YAML::Node& node, const char* valueName, const AValue& value) const;

private:
    virtual void ReadDescriptionNode(const YAML::Node& node) = 0;
    virtual void WriteDescriptionNode(YAML::Node& node) const = 0;

protected:
    std::string fName;
};

template<class ADerived>
class IDescriptionSingleton : public Environment::Resource::Singleton<ADerived>,
                              public IDescription {
protected:
    using IDescription::IDescription;
};

template<class T>
concept IsDescription =
    std::derived_from<T, IDescriptionSingleton<T>> and
    std::is_final_v<T> and
    not std::copyable<T> and
    requires {
    { T::Instance() } -> std::same_as<T&>;
};

} // namespace MACE::Core::Geometry

#include "MACE/Core/Geometry/IDescription.inl"
