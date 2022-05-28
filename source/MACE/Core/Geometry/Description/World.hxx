#pragma once

#include "MACE/Core/Geometry/IDescription.hxx"

namespace MACE::Core::Geometry::Description {

class World final : public IDescription {
public:
    static World& Instance() noexcept;

private:
    World();
    ~World() noexcept = default;
    World(const World&) = delete;
    World& operator=(const World&) = delete;

public:
    const auto& GetHalfXExtent() const { return fHalfXExtent; }
    const auto& GetHalfYExtent() const { return fHalfYExtent; }
    const auto& GetHalfZExtent() const { return fHalfZExtent; }

    void SetHalfXExtent(double val) { fHalfXExtent = val; }
    void SetHalfYExtent(double val) { fHalfYExtent = val; }
    void SetHalfZExtent(double val) { fHalfZExtent = val; }

private:
    void ReadDescriptionNode(const YAML::Node& node) override;
    void WriteDescriptionNode(YAML::Node& node) const override;

private:
    double fHalfXExtent;
    double fHalfYExtent;
    double fHalfZExtent;
};

} // namespace MACE::Core::Geometry::Description
