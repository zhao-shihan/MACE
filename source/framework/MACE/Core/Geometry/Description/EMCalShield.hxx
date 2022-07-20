#pragma once

#include "MACE/Core/Geometry/Description/EMCalField.hxx"

namespace MACE::Core::Geometry::Description {

class EMCalShield final : public ISingletonDescription<EMCalShield> {
    friend Environment::Resource::SingletonFactory;

private:
    EMCalShield();
    ~EMCalShield() noexcept = default;
    EMCalShield(const EMCalShield&) = delete;
    EMCalShield& operator=(const EMCalShield&) = delete;

public:
    const auto& GetInnerRadius() const { return fInnerRadius; }
    const auto& GetInnerLength() const { return fInnerLength; }
    const auto& GetWindowRadius() const { return fWindowRadius; }
    const auto& GetThickness() const { return fThickness; }

    void SetInnerRadius(double val) { fInnerRadius = val; }
    void SetInnerLength(double val) { fInnerLength = val; }
    void SetWindowRadius(double val) { fWindowRadius = val; }
    void SetThickness(double val) { fThickness = val; }

    // Next 1 method should only use for geometry construction.

    auto CalcTransform() const { return EMCalField::Instance().CalcTransform(); }

private:
    void ReadDescriptionNode(const YAML::Node& node) override;
    void WriteDescriptionNode(YAML::Node& node) const override;

private:
    double fInnerRadius;
    double fInnerLength;
    double fWindowRadius;
    double fThickness;
};

} // namespace MACE::Core::Geometry::Description
