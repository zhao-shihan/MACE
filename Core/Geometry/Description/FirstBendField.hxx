#pragma once

#include "Geometry/Description/FirstTransportField.hxx"

namespace MACE::Geometry::Description {

class FirstBendField final : public IDescription {
public:
    static FirstBendField& Instance() noexcept;

private:
    FirstBendField() = default;
    ~FirstBendField() noexcept = default;
    FirstBendField(const FirstBendField&) = delete;
    FirstBendField& operator=(const FirstBendField&) = delete;

public:
    [[nodiscard]] std::string GetName() const override { return "FirstBendField"; }
    [[nodiscard]] std::string GetOverallDescription() const override { return ""; }
    [[nodiscard]] std::string GetMaterialDescription() const override { return ""; }
    [[nodiscard]] std::string GetShapeDescription() const override { return ""; }
    [[nodiscard]] std::string GetMotherDescription() const override { return ""; }
    [[nodiscard]] std::string GetTranslationDescription() const override { return ""; }
    [[nodiscard]] std::string GetRotationDescription() const override { return ""; }

    [[nodiscard]] const auto& GetRadius() const { return FirstTransportField::Instance().GetRadius(); }
    [[nodiscard]] const auto& GetBendRadius() const { return fBendRadius; }
    [[nodiscard]] G4Transform3D GetTransform() const;

    void SetBendRadius(double val) { fBendRadius = val; }

private:
    double fBendRadius = 50_cm;
};

} // namespace MACE::Geometry::Description
