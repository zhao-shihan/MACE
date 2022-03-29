#pragma once

#include "Core/Geometry/IDescription.hxx"

#include <cmath>

namespace MACE::Geometry::Description {

class SelectorField final : public IDescription {
public:
    static SelectorField& Instance() noexcept;

private:
    SelectorField() = default;
    ~SelectorField() noexcept = default;
    SelectorField(const SelectorField&) = delete;
    SelectorField& operator=(const SelectorField&) = delete;

public:
    std::string GetName() const override { return "SelectorField"; }
    std::string GetOverallDescription() const override { return ""; }
    std::string GetMaterialDescription() const override { return ""; }
    std::string GetShapeDescription() const override { return ""; }
    std::string GetMotherDescription() const override { return ""; }
    std::string GetTranslationDescription() const override { return ""; }
    std::string GetRotationDescription() const override { return ""; }

    const auto& GetRadius() const { return fRadius; }
    const auto& GetLength() const { return fLength; }
    const auto& GetZPosition() const { return fZPosition; }

    void SetRadius(double val) { fRadius = val; }
    void SetLength(double val) { fLength = val; }
    void SetZPosition(double val) { fZPosition = val; }

private:
    double fRadius = 7.5_cm;
    double fLength = 30_cm;
    double fZPosition = 20_cm;
};

} // namespace MACE::Geometry::Description
