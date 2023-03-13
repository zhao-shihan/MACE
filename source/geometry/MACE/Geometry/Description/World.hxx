#pragma once

#include "MACE/Geometry/DescriptionBase.hxx"

namespace MACE::Geometry::Description {

class World final : public DescriptionSingletonBase<World> {
    friend Env::Memory::SingletonFactory;

private:
    World();
    ~World() noexcept = default;
    World(const World&) = delete;
    World& operator=(const World&) = delete;

public:
    const auto& HalfXExtent() const { return fHalfXExtent; }
    const auto& HalfYExtent() const { return fHalfYExtent; }
    const auto& HalfZExtent() const { return fHalfZExtent; }

    void HalfXExtent(double val) { fHalfXExtent = val; }
    void HalfYExtent(double val) { fHalfYExtent = val; }
    void HalfZExtent(double val) { fHalfZExtent = val; }

private:
    void ImportValues(const YAML::Node& node) override;
    void ExportValues(YAML::Node& node) const override;

private:
    double fHalfXExtent;
    double fHalfYExtent;
    double fHalfZExtent;
};

} // namespace MACE::Geometry::Description
