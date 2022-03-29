#pragma once

#include "Core/Geometry/Description/SecondTransportField.hxx"

namespace MACE::Geometry::Description {

class SecondBendField final : public IDescription {
public:
    static SecondBendField& Instance() noexcept;

private:
    SecondBendField() = default;
    ~SecondBendField() noexcept = default;
    SecondBendField(const SecondBendField&) = delete;
    SecondBendField& operator=(const SecondBendField&) = delete;

public:
    std::string GetName() const override { return "SecondBendField"; }
    std::string GetOverallDescription() const override { return ""; }
    std::string GetMaterialDescription() const override { return ""; }
    std::string GetShapeDescription() const override { return ""; }
    std::string GetMotherDescription() const override { return ""; }
    std::string GetTranslationDescription() const override { return ""; }
    std::string GetRotationDescription() const override { return ""; }

    const auto& GetRadius() const { return SecondTransportField::Instance().GetRadius(); }
    const auto& GetBendRadius() const { return fBendRadius; }
    G4Transform3D GetTransform() const;

    void SetBendRadius(double val) { fBendRadius = val; }

private:
    double fBendRadius = 50_cm;
};

} // namespace MACE::Geometry::Description
