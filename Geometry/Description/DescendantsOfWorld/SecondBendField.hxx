#pragma once

#include "Geometry/Description/DescendantsOfWorld/SecondTransportField.hxx"

class MACE::Geometry::Description::SecondBendField final :
    public MACE::Geometry::Interface::Description {
public:
    static SecondBendField& Instance() noexcept;

private:
    SecondBendField() noexcept = default;
    ~SecondBendField() noexcept = default;
    SecondBendField(const SecondBendField&) = delete;
    SecondBendField& operator=(const SecondBendField&) = delete;

public:
    [[nodiscard]] std::string GetName()                   const override { return "SecondBendField"; }
    [[nodiscard]] std::string GetOverallDescription()     const override { return ""; }
    [[nodiscard]] std::string GetMaterialDescription()    const override { return ""; }
    [[nodiscard]] std::string GetShapeDescription()       const override { return ""; }
    [[nodiscard]] std::string GetMotherDescription()      const override { return ""; }
    [[nodiscard]] std::string GetTranslationDescription() const override { return ""; }
    [[nodiscard]] std::string GetRotationDescription()    const override { return ""; }

    [[nodiscard]] const auto& GetRadius()     const { return SecondTransportField::Instance().GetRadius(); }
    [[nodiscard]] const auto& GetBendRadius() const { return fBendRadius; }
    [[nodiscard]] G4Transform3D GetTransform()  const;

    void SetBendRadius(double val) { fBendRadius = val; }

private:
    double fBendRadius = 50_cm;
};
