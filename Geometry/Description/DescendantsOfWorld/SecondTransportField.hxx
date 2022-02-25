#pragma once

#include "Geometry/Description/DescendantsOfWorld/FirstBendField.hxx"

class MACE::Geometry::Description::SecondTransportField final :
    public MACE::Geometry::Interface::Description {
public:
    static SecondTransportField& Instance() noexcept;

private:
    SecondTransportField() noexcept = default;
    ~SecondTransportField() noexcept = default;
    SecondTransportField(const SecondTransportField&) = delete;
    SecondTransportField& operator=(const SecondTransportField&) = delete;

public:
    [[nodiscard]] std::string GetName()                   const override { return "SecondTransportField"; }
    [[nodiscard]] std::string GetOverallDescription()     const override { return ""; }
    [[nodiscard]] std::string GetMaterialDescription()    const override { return ""; }
    [[nodiscard]] std::string GetShapeDescription()       const override { return ""; }
    [[nodiscard]] std::string GetMotherDescription()      const override { return ""; }
    [[nodiscard]] std::string GetTranslationDescription() const override { return "As this GetTranslation()"; }
    [[nodiscard]] std::string GetRotationDescription()    const override { return ""; }

    [[nodiscard]] const auto& GetLength() const { return fLength; }
    [[nodiscard]] const auto& GetRadius() const { return FirstBendField::Instance().GetRadius(); }
    [[nodiscard]] inline auto GetTransform() const;

    void SetLength(double val) { fLength = val; }

private:
    double fLength = 100_cm;
};

inline auto MACE::Geometry::Description::SecondTransportField::GetTransform() const {
    auto&& firstBendField = FirstBendField::Instance();
    auto transX = firstBendField.GetTransform().dx() + fLength / 2;
    auto transY = firstBendField.GetTransform().dy();
    auto transZ = firstBendField.GetTransform().dz() + firstBendField.GetBendRadius();
    return G4Transform3D(G4RotationMatrix(G4ThreeVector(0, 1, 0), M_PI_2), G4ThreeVector(transX, transY, transZ));
}
