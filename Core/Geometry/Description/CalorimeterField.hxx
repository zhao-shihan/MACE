#pragma once

#include "Core/Geometry/Description/ThirdTransportField.hxx"

namespace MACE::Geometry::Description {

class CalorimeterField final : public IDescription {
public:
    static CalorimeterField& Instance() noexcept;

private:
    CalorimeterField() = default;
    ~CalorimeterField() noexcept = default;
    CalorimeterField(const CalorimeterField&) = delete;
    CalorimeterField& operator=(const CalorimeterField&) = delete;

public:
    std::string GetName() const override { return "CalorimeterField"; }
    std::string GetOverallDescription() const override { return ""; }
    std::string GetMaterialDescription() const override { return ""; }
    std::string GetShapeDescription() const override { return ""; }
    std::string GetMotherDescription() const override { return ""; }
    std::string GetTranslationDescription() const override { return ""; }
    std::string GetRotationDescription() const override { return ""; }

    const auto& GetRadius() const { return fRadius; }
    const auto& GetLength() const { return fLength; }
    G4Transform3D GetTransform() const;

    void SetRadius(double val) { fRadius = val; }
    void SetLength(double val) { fLength = val; }

private:
    double fRadius = 25_cm;
    double fLength = 70_cm;
};

} // namespace MACE::Geometry::Description
