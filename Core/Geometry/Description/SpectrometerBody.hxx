#pragma once

#include "Core/Geometry/IDescription.hxx"

namespace MACE::Core::Geometry::Description {

class SpectrometerBody final : public IDescription {
public:
    static SpectrometerBody& Instance() noexcept;

private:
    SpectrometerBody();
    ~SpectrometerBody() noexcept = default;
    SpectrometerBody(const SpectrometerBody&) = delete;
    SpectrometerBody& operator=(const SpectrometerBody&) = delete;

public:
    const auto& GetGasInnerRadius() const { return fGasInnerRadius; }
    const auto& GetGasOuterRadius() const { return fGasOuterRadius; }
    const auto& GetGasInnerLength() const { return fGasInnerLength; }
    const auto& GetGasOuterLength() const { return fGasOuterLength; }
    const auto& GetShellInnerThickness() const { return fShellInnerThickness; }
    const auto& GetShellSideThickness() const { return fShellSideThickness; }
    const auto& GetShellOuterThickness() const { return fShellOuterThickness; }

    void SetGasInnerRadius(double val) { fGasInnerRadius = val; }
    void SetGasOuterRadius(double val) { fGasOuterRadius = val; }
    void SetGasInnerLength(double val) { fGasInnerLength = val; }
    void SetGasOuterLength(double val) { fGasOuterLength = val; }
    void SetShellInnerThickness(double val) { fShellInnerThickness = val; }
    void SetShellSideThickness(double val) { fShellSideThickness = val; }
    void SetShellOuterThickness(double val) { fShellOuterThickness = val; }

private:
    double fGasInnerRadius;
    double fGasOuterRadius;
    double fGasInnerLength;
    double fGasOuterLength;
    double fShellInnerThickness;
    double fShellSideThickness;
    double fShellOuterThickness;
};

} // namespace MACE::Core::Geometry::Description
