#pragma once

#include "MACE/Detector/Description/DescriptionBase.h++"
#include "MACE/Detector/Description/EMCField.h++"

namespace MACE::Detector::Description {

class EMCShield final : public DescriptionSingletonBase<EMCShield> {
    friend Env::Memory::SingletonInstantiator;

private:
    EMCShield();
    ~EMCShield() = default;

public:
    auto InnerRadius() const -> const auto& { return fInnerRadius; }
    auto InnerLength() const -> const auto& { return fInnerLength; }
    auto GapAroundWindow() const -> const auto& { return fGapAroundWindow; }
    auto Thickness() const -> const auto& { return fThickness; }

    auto InnerRadius(double val) -> void { fInnerRadius = val; }
    auto InnerLength(double val) -> void { fInnerLength = val; }
    auto GapAroundWindow(double val) -> void { fGapAroundWindow = val; }
    auto Thickness(double val) -> void { fThickness = val; }

private:
    auto ImportValues(const YAML::Node& node) -> void override;
    auto ExportValues(YAML::Node& node) const -> void override;

private:
    double fInnerRadius;
    double fInnerLength;
    double fGapAroundWindow;
    double fThickness;
};

} // namespace MACE::Detector::Description
