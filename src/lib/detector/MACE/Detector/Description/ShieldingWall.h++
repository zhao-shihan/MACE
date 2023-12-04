#pragma once

#include "MACE/Detector/Description/DescriptionBase.h++"

namespace MACE::Detector::Description {

class ShieldingWall final : public DescriptionSingletonBase<ShieldingWall> {
    friend Env::Memory::SingletonFactory;

private:
    ShieldingWall();

public:
    const auto& Height() const { return fHeight; }
    const auto& Width() const { return fWidth; }
    const auto& Thickness() const { return fThickness; }

    void Height(double val) { fHeight = val; }
    void Width(double val) { fWidth = val; }
    void Thickness(double val) { fThickness = val; }

private:
    void ImportValues(const YAML::Node& node) override;
    void ExportValues(YAML::Node& node) const override;

private:
    double fHeight;
    double fWidth;
    double fThickness;
};

} // namespace MACE::Detector::Description
