#pragma once

#include "yaml-cpp/yaml.h"

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

private:
    virtual void ReadImpl(const YAML::Node& node) = 0;
    virtual void WriteImpl(YAML::Node& node) const = 0;

protected:
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
