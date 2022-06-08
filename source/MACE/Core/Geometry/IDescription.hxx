#pragma once

#include "yaml-cpp/yaml.h"

#include <optional>
#include <string>
#include <string_view>

namespace MACE::Core::Geometry {

class IDescription {
public:
    IDescription(const std::string& name);
    virtual ~IDescription() noexcept = default;
    IDescription(const IDescription&) = delete;
    IDescription& operator=(const IDescription&) = delete;

    const auto& GetName() const { return fName; }

    void Read(const YAML::Node& geomYaml);
    void Write(YAML::Node& geomYaml) const;

protected:
    template<typename ValueT, typename ReadAsT = ValueT>
    void ReadValueNode(const YAML::Node& node, const char* valueName, ValueT& value);
    template<typename ValueT, typename WriteAsT = ValueT>
    void WriteValueNode(YAML::Node& node, const char* valueName, const ValueT& value) const;

private:
    virtual void ReadDescriptionNode(const YAML::Node& node) = 0;
    virtual void WriteDescriptionNode(YAML::Node& node) const = 0;

protected:
    std::string fName;
};

template<class T>
concept IsDescription =
    std::derived_from<T, IDescription> and
    std::is_final_v<T> and
    not std::copyable<T> and
    requires {
    { T::Instance() } -> std::same_as<T&>;
};

} // namespace MACE::Core::Geometry

#include "MACE/Core/Geometry/IDescription.ixx"
