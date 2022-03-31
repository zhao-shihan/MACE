#pragma once

#include "Core/Geometry/IDescription.hxx"

namespace MACE::Core::Geometry::Description {

class Collimator final : public IDescription {
public:
    static Collimator& Instance() noexcept;

private:
    Collimator() = default;
    ~Collimator() noexcept = default;
    Collimator(const Collimator&) = delete;
    Collimator& operator=(const Collimator&) = delete;

public:
    std::string GetName() const override { return "Collimator"; }
    std::string GetOverallDescription() const override { return ""; }
    std::string GetMaterialDescription() const override { return ""; }
    std::string GetShapeDescription() const override { return ""; }
    std::string GetMotherDescription() const override { return ""; }
    std::string GetTranslationDescription() const override { return ""; }
    std::string GetRotationDescription() const override { return ""; }

    const auto& GetInnerRadius() const { return fInnerRadius; }
    const auto& GetOuterRadius() const { return fOuterRadius; }
    const auto& GetLength() const { return fLength; }
    const auto& GetThickness() const { return fThickness; }
    const auto& GetZPosition() const { return fZPosition; }
    const auto& GetCount() const { return fCount; }

    void SetInnerRadius(double val) { fInnerRadius = val; }
    void SetOuterRadius(double val) { fOuterRadius = val; }
    void SetLength(double val) { fLength = val; }
    void SetThickness(double val) { fThickness = val; }
    void SetZPosition(double val) { fZPosition = val; }
    void SetCount(int val) { fCount = val; }

private:
    double fInnerRadius = 5_mm;
    double fOuterRadius = 65_mm;
    double fLength = 30_cm;
    double fZPosition = -20_cm;
    double fThickness = 0.75_mm;
    int fCount = 7;
};

} // namespace MACE::Core::Geometry::Description
