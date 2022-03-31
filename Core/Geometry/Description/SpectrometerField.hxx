#pragma once

#include "Core/Geometry/IDescription.hxx"

namespace MACE::Core::Geometry::Description {

class SpectrometerField final : public IDescription {
public:
    static SpectrometerField& Instance() noexcept;

private:
    SpectrometerField() = default;
    ~SpectrometerField() noexcept = default;
    SpectrometerField(const SpectrometerField&) = delete;
    SpectrometerField& operator=(const SpectrometerField&) = delete;

public:
    std::string GetName() const override { return "SpectrometerField"; }
    std::string GetOverallDescription() const override { return ""; }
    std::string GetMaterialDescription() const override { return ""; }
    std::string GetShapeDescription() const override { return ""; }
    std::string GetMotherDescription() const override { return ""; }
    std::string GetTranslationDescription() const override { return ""; }
    std::string GetRotationDescription() const override { return ""; }

    const auto& GetRadius() const { return fRadius; }
    const auto& GetLength() const { return fLength; }

    void SetRadius(double val) { fRadius = val; }
    void SetLength(double val) { fLength = val; }

private:
    double fRadius = 71_cm;
    double fLength = 220_cm;
};

} // namespace MACE::Core::Geometry::Description
