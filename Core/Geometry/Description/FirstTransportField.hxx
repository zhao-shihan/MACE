#pragma once

#include "Core/Geometry/Description/SpectrometerField.hxx"

#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"

namespace MACE::Geometry::Description {

class FirstTransportField final : public IDescription {
public:
    static FirstTransportField& Instance() noexcept;

private:
    FirstTransportField() = default;
    ~FirstTransportField() noexcept = default;
    FirstTransportField(const FirstTransportField&) = delete;
    FirstTransportField& operator=(const FirstTransportField&) = delete;

public:
    std::string GetName() const override { return "FirstTransportField"; }
    std::string GetOverallDescription() const override { return ""; }
    std::string GetMaterialDescription() const override { return ""; }
    std::string GetShapeDescription() const override { return ""; }
    std::string GetMotherDescription() const override { return ""; }
    std::string GetTranslationDescription() const override { return ""; }
    std::string GetRotationDescription() const override { return ""; }

    const auto& GetRadius() const { return fRadius; }
    const auto& GetLength() const { return fLength; }
    G4Transform3D GetTransform() const;

    void SetRaidus(double val) { fRadius = val; }
    void SetLength(double val) { fLength = val; }

private:
    double fRadius = 12.6_cm;
    double fLength = 20_cm;
};

} // namespace MACE::Geometry::Description
