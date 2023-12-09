#pragma once

#include "MACE/Detector/Description/DescriptionBase.h++"

namespace MACE::Detector::Description {

class World final : public DescriptionSingletonBase<World> {
    friend Env::Memory::SingletonFactory;

private:
    World();
    ~World() = default;

public:
    const auto& HalfXExtent() const { return fHalfXExtent; }
    const auto& HalfYExtent() const { return fHalfYExtent; }
    const auto& HalfZExtent() const { return fHalfZExtent; }

    void HalfXExtent(double val) { fHalfXExtent = val; }
    void HalfYExtent(double val) { fHalfYExtent = val; }
    void HalfZExtent(double val) { fHalfZExtent = val; }

private:
    auto ImportValues(const YAML::Node& node) -> void override;
    auto ExportValues(YAML::Node& node) const -> void override;

private:
    double fHalfXExtent;
    double fHalfYExtent;
    double fHalfZExtent;
};

} // namespace MACE::Detector::Description
