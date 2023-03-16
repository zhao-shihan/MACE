#pragma once

#include "MACE/Detector/Description/EMCalField.hxx"

namespace MACE::Detector::Description {

class EMCalShield final : public DescriptionSingletonBase<EMCalShield> {
    friend Env::Memory::SingletonFactory;

private:
    EMCalShield();
    ~EMCalShield() noexcept = default;
    EMCalShield(const EMCalShield&) = delete;
    EMCalShield& operator=(const EMCalShield&) = delete;

public:
    const auto& InnerRadius() const { return fInnerRadius; }
    const auto& InnerLength() const { return fInnerLength; }
    const auto& WindowRadius() const { return fWindowRadius; }
    const auto& Thickness() const { return fThickness; }

    void InnerRadius(double val) { fInnerRadius = val; }
    void InnerLength(double val) { fInnerLength = val; }
    void WindowRadius(double val) { fWindowRadius = val; }
    void Thickness(double val) { fThickness = val; }

    // Next 1 method should only use for geometry construction.

    auto CalcTransform() const { return EMCalField::Instance().CalcTransform(); }

private:
    void ImportValues(const YAML::Node& node) override;
    void ExportValues(YAML::Node& node) const override;

private:
    double fInnerRadius;
    double fInnerLength;
    double fWindowRadius;
    double fThickness;
};

} // namespace MACE::Geometry::Description
