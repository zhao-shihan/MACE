#pragma once

#include "Core/Geometry/IDescription.hxx"

namespace MACE::Geometry::Description {

class SpectrometerField final : public IDescription {
public:
    static SpectrometerField& Instance() noexcept;

private:
    SpectrometerField() = default;
    ~SpectrometerField() noexcept = default;
    SpectrometerField(const SpectrometerField&) = delete;
    SpectrometerField& operator=(const SpectrometerField&) = delete;

public:
    [[nodiscard]] std::string GetName() const override { return "SpectrometerField"; }
    [[nodiscard]] std::string GetOverallDescription() const override { return ""; }
    [[nodiscard]] std::string GetMaterialDescription() const override { return ""; }
    [[nodiscard]] std::string GetShapeDescription() const override { return ""; }
    [[nodiscard]] std::string GetMotherDescription() const override { return ""; }
    [[nodiscard]] std::string GetTranslationDescription() const override { return ""; }
    [[nodiscard]] std::string GetRotationDescription() const override { return ""; }

    [[nodiscard]] const auto& GetRadius() const { return fRadius; }
    [[nodiscard]] const auto& GetLength() const { return fLength; }

    void SetRadius(double val) { fRadius = val; }
    void SetLength(double val) { fLength = val; }

private:
    double fRadius = 71_cm;
    double fLength = 220_cm;
};

} // namespace MACE::Geometry::Description
