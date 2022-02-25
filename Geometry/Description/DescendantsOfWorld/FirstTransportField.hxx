#pragma once

#include "Geometry/Description/DescendantsOfWorld/SpectrometerField.hxx"

class MACE::Geometry::Description::FirstTransportField final :
    public MACE::Geometry::Interface::Description {
public:
    static FirstTransportField& Instance() noexcept;

private:
    FirstTransportField() noexcept = default;
    ~FirstTransportField() noexcept = default;
    FirstTransportField(const FirstTransportField&) = delete;
    FirstTransportField& operator=(const FirstTransportField&) = delete;

public:
    [[nodiscard]] std::string GetName()                   const override { return "FirstTransportField"; }
    [[nodiscard]] std::string GetOverallDescription()     const override { return ""; }
    [[nodiscard]] std::string GetMaterialDescription()    const override { return ""; }
    [[nodiscard]] std::string GetShapeDescription()       const override { return ""; }
    [[nodiscard]] std::string GetMotherDescription()      const override { return ""; }
    [[nodiscard]] std::string GetTranslationDescription() const override { return ""; }
    [[nodiscard]] std::string GetRotationDescription()    const override { return ""; }

    [[nodiscard]] const auto& GetRadius()    const { return fRadius; }
    [[nodiscard]] const auto& GetLength()    const { return fLength; }
    [[nodiscard]] inline auto GetTransform() const;

    void SetRaidus(double val) { fRadius = val; }
    void SetLength(double val) { fLength = val; }

private:
    double fRadius = 10.5_cm;
    double fLength = 20_cm;
};

inline auto MACE::Geometry::Description::FirstTransportField::GetTransform() const {
    return G4Transform3D(
        G4RotationMatrix(),
        G4ThreeVector(0, 0, SpectrometerField::Instance().GetLength() / 2 + fLength / 2));
}
