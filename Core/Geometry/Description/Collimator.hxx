#pragma once

#include "Core/Geometry/IDescription.hxx"

namespace MACE::Geometry::Description {

class Collimator final : public IDescription {
public:
    static Collimator& Instance() noexcept;

private:
    Collimator() = default;
    ~Collimator() noexcept = default;
    Collimator(const Collimator&) = delete;
    Collimator& operator=(const Collimator&) = delete;

public:
    [[nodiscard]] std::string GetName() const override { return "Collimator"; }
    [[nodiscard]] std::string GetOverallDescription() const override { return ""; }
    [[nodiscard]] std::string GetMaterialDescription() const override { return ""; }
    [[nodiscard]] std::string GetShapeDescription() const override { return ""; }
    [[nodiscard]] std::string GetMotherDescription() const override { return ""; }
    [[nodiscard]] std::string GetTranslationDescription() const override { return ""; }
    [[nodiscard]] std::string GetRotationDescription() const override { return ""; }

    [[nodiscard]] const auto& GetInnerRadius() const { return fInnerRadius; }
    [[nodiscard]] const auto& GetOuterRadius() const { return fOuterRadius; }
    [[nodiscard]] const auto& GetLength() const { return fLength; }
    [[nodiscard]] const auto& GetThickness() const { return fThickness; }
    [[nodiscard]] const auto& GetZPosition() const { return fZPosition; }
    [[nodiscard]] const auto& GetCount() const { return fCount; }

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

} // namespace MACE::Geometry::Description
