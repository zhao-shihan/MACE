#pragma once

#include "MACE/Core/Geometry/IDescription.hxx"

namespace MACE::Core::Geometry::Description {

class World final : public ISingletonDescription<World> {
    friend Environment::Memory::SingletonFactory;

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
    void ImportValues(const YAML::Node& node) override;
    void ExportValues(YAML::Node& node) const override;

private:
    double fHalfXExtent;
    double fHalfYExtent;
    double fHalfZExtent;
};

} // namespace MACE::Core::Geometry::Description
