#pragma once

#include "MACE/Geometry/DescriptionBase.hxx"

namespace MACE::Geometry::Description {

class Collimator final : public DescriptionSingletonBase<Collimator> {
    friend Env::Memory::SingletonFactory;

private:
    Collimator();
    ~Collimator() noexcept = default;
    Collimator(const Collimator&) = delete;
    Collimator& operator=(const Collimator&) = delete;

public:
    const auto& InnerRadius() const { return fInnerRadius; }
    const auto& OuterRadius() const { return fOuterRadius; }
    const auto& Length() const { return fLength; }
    const auto& Thickness() const { return fThickness; }
    const auto& AxialPosition() const { return fAxialPosition; }
    const auto& Count() const { return fCount; }

    void InnerRadius(double val) { fInnerRadius = val; }
    void OuterRadius(double val) { fOuterRadius = val; }
    void Length(double val) { fLength = val; }
    void Thickness(double val) { fThickness = val; }
    void AxialPosition(double val) { fAxialPosition = val; }
    void Count(int val) { fCount = val; }

private:
    void ImportValues(const YAML::Node& node) override;
    void ExportValues(YAML::Node& node) const override;

private:
    double fInnerRadius;
    double fOuterRadius;
    double fLength;
    double fAxialPosition;
    double fThickness;
    int fCount;
};

} // namespace MACE::Geometry::Description
