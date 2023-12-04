#pragma once

#include "MACE/Detector/Description/EMCField.h++"

namespace MACE::Detector::Description {

class EMCShield final : public DescriptionSingletonBase<EMCShield> {
    friend Env::Memory::SingletonFactory;

private:
    EMCShield();

public:
    auto InnerRadius() const -> const auto& { return fInnerRadius; }
    auto InnerLength() const -> const auto& { return fInnerLength; }
    auto WindowRadius() const -> const auto& { return fWindowRadius; }
    auto Thickness() const -> const auto& { return fThickness; }

    auto InnerRadius(double val) -> void { fInnerRadius = val; }
    auto InnerLength(double val) -> void { fInnerLength = val; }
    auto WindowRadius(double val) -> void { fWindowRadius = val; }
    auto Thickness(double val) -> void { fThickness = val; }

    // Next 1 method should only use for geometry construction.

    auto CalcTransform() const { return EMCField::Instance().CalcTransform(); }

private:
    auto ImportValues(const YAML::Node& node) -> void override;
    auto ExportValues(YAML::Node& node) const -> void override;

private:
    double fInnerRadius;
    double fInnerLength;
    double fWindowRadius;
    double fThickness;
};

} // namespace MACE::Detector::Description
