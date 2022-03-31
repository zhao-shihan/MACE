#pragma once

#include "yaml-cpp/yaml.h"

namespace MACE::Core::Geometry {

class IDescription {
protected:
    IDescription(const std::string& name);
    virtual ~IDescription() noexcept = default;
    IDescription(const IDescription&) = delete;
    IDescription& operator=(const IDescription&) = delete;

public:
    const auto& GetName() const { return fName; }
    virtual void Read(const YAML::Node& geomYaml) = 0;
    virtual void Write(YAML::Node& geomYaml) const = 0;

private:
    std::string fName;
};

template<class T>
concept IsDescription =
    std::derived_from<T, IDescription> and
    not std::copyable<T> and
    requires {
    { T::Instance() } -> std::same_as<T&>;
};

} // namespace MACE::Core::Geometry
