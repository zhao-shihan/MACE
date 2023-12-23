#pragma once

#include "MACE/Detector/Description/DescriptionBase.h++"

namespace MACE::Detector::Description {

class ShieldingWall final : public DescriptionSingletonBase<ShieldingWall> {
    friend Env::Memory::SingletonInstantiator;

private:
    ShieldingWall();
    ~ShieldingWall() = default;

public:
    auto Thickness() const -> const auto& { return fThickness; }

    auto Thickness(double val) -> void { fThickness = val; }

private:
    auto ImportValues(const YAML::Node& node) -> void override;
    auto ExportValues(YAML::Node& node) const -> void override;

private:
    double fThickness;
};

} // namespace MACE::Detector::Description
