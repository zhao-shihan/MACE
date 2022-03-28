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
    [[nodiscard]] std::string GetName() const override { return "CalorimeterField"; }
    [[nodiscard]] std::string GetOverallDescription() const override { return ""; }
    [[nodiscard]] std::string GetMaterialDescription() const override { return ""; }
    [[nodiscard]] std::string GetShapeDescription() const override { return ""; }
    [[nodiscard]] std::string GetMotherDescription() const override { return ""; }
    [[nodiscard]] std::string GetTranslationDescription() const override { return ""; }
    [[nodiscard]] std::string GetRotationDescription() const override { return ""; }

    [[nodiscard]] const auto& GetRadius() const { return fRadius; }
    [[nodiscard]] const auto& GetLength() const { return fLength; }
    [[nodiscard]] G4Transform3D GetTransform() const;

    void SetRadius(double val) { fRadius = val; }
    void SetLength(double val) { fLength = val; }

private:
    double fRadius = 23_cm;
    double fLength = 50_cm;
};

} // namespace MACE::Geometry::Description
