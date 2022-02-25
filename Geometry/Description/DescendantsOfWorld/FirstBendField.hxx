#pragma once

#include "Geometry/Description/DescendantsOfWorld/FirstTransportField.hxx"

class MACE::Geometry::Description::FirstBendField final :
    public MACE::Geometry::Interface::Description {
public:
    static FirstBendField& Instance() noexcept;

private:
    FirstBendField() noexcept = default;
    ~FirstBendField() noexcept = default;
    FirstBendField(const FirstBendField&) = delete;
    FirstBendField& operator=(const FirstBendField&) = delete;

public:
    [[nodiscard]] std::string GetName()                   const override { return "FirstBendField"; }
    [[nodiscard]] std::string GetOverallDescription()     const override { return ""; }
    [[nodiscard]] std::string GetMaterialDescription()    const override { return ""; }
    [[nodiscard]] std::string GetShapeDescription()       const override { return ""; }
    [[nodiscard]] std::string GetMotherDescription()      const override { return ""; }
    [[nodiscard]] std::string GetTranslationDescription() const override { return ""; }
    [[nodiscard]] std::string GetRotationDescription()    const override { return ""; }

    [[nodiscard]] const auto& GetRadius()     const { return FirstTransportField::Instance().GetRadius(); }
    [[nodiscard]] const auto& GetBendRadius() const { return fBendRadius; }
    [[nodiscard]] inline auto GetTransform()  const;

    void SetBendRadius(double val) { fBendRadius = val; }

private:
    double fBendRadius = 50_cm;
};

inline auto MACE::Geometry::Description::FirstBendField::GetTransform() const {
    auto&& firstTransportField = FirstTransportField::Instance();
    auto transX = firstTransportField.GetTransform().dx() + fBendRadius;
    auto transY = firstTransportField.GetTransform().dy();
    auto transZ = firstTransportField.GetTransform().dz() + firstTransportField.GetLength() / 2;
    return G4Transform3D(G4RotationMatrix(G4ThreeVector(1, 0, 0), M_PI_2), G4ThreeVector(transX, transY, transZ));
}
