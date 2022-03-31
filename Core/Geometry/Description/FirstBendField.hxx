#pragma once

#include "Core/Geometry/Description/FirstTransportField.hxx"

namespace MACE::Core::Geometry::Description {

class FirstBendField final : public IDescription {
public:
    static FirstBendField& Instance() noexcept;

private:
    FirstBendField() = default;
    ~FirstBendField() noexcept = default;
    FirstBendField(const FirstBendField&) = delete;
    FirstBendField& operator=(const FirstBendField&) = delete;

public:
    std::string GetName() const override { return "FirstBendField"; }
    std::string GetOverallDescription() const override { return ""; }
    std::string GetMaterialDescription() const override { return ""; }
    std::string GetShapeDescription() const override { return ""; }
    std::string GetMotherDescription() const override { return ""; }
    std::string GetTranslationDescription() const override { return ""; }
    std::string GetRotationDescription() const override { return ""; }

    const auto& GetRadius() const { return FirstTransportField::Instance().GetRadius(); }
    const auto& GetBendRadius() const { return fBendRadius; }
    G4Transform3D GetTransform() const;

    void SetBendRadius(double val) { fBendRadius = val; }

private:
    double fBendRadius = 50_cm;
};

} // namespace MACE::Core::Geometry::Description
