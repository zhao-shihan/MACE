#pragma once

#include "Geometry/Description/DescendantsOfWorld/SecondBendField.hxx"

class MACE::Geometry::Description::ThirdTransportField final :
    public MACE::Geometry::Interface::Description {
public:
    static ThirdTransportField& Instance() noexcept;

private:
    ThirdTransportField() noexcept = default;
    ~ThirdTransportField() noexcept = default;
    ThirdTransportField(const ThirdTransportField&) = delete;
    ThirdTransportField& operator=(const ThirdTransportField&) = delete;

public:
    [[nodiscard]] std::string GetName()                   const override { return "ThirdTransportField"; }
    [[nodiscard]] std::string GetOverallDescription()     const override { return ""; }
    [[nodiscard]] std::string GetMaterialDescription()    const override { return ""; }
    [[nodiscard]] std::string GetShapeDescription()       const override { return ""; }
    [[nodiscard]] std::string GetMotherDescription()      const override { return ""; }
    [[nodiscard]] std::string GetTranslationDescription() const override { return ""; }
    [[nodiscard]] std::string GetRotationDescription()    const override { return ""; }

    [[nodiscard]] const auto& GetLength() const { return fLength; }
    [[nodiscard]] const auto& GetRadius() const { return SecondBendField::Instance().GetRadius(); }
    [[nodiscard]] inline auto GetTransform() const;

    void SetLength(double val) { fLength = val; }

private:
    double fLength = 20_cm;
};

inline auto MACE::Geometry::Description::ThirdTransportField::GetTransform() const {
    auto&& secondBendField = SecondBendField::Instance();
    auto transX = secondBendField.GetTransform().dx() + secondBendField.GetBendRadius();
    auto transY = secondBendField.GetTransform().dy();
    auto transZ = secondBendField.GetTransform().dz() + fLength / 2;
    return G4Transform3D(G4RotationMatrix(), G4ThreeVector(transX, transY, transZ));
}
