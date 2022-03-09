#pragma once

#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"

#include "Geometry/Description/DescendantsOfWorld/SpectrometerField.hxx"

class MACE::Geometry::Description::FirstTransportField final :
    public MACE::Geometry::Interface::Description {
public:
    static FirstTransportField& Instance() noexcept;

private:
    FirstTransportField() = default;
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
    [[nodiscard]] G4Transform3D GetTransform() const;

    void SetRaidus(double val) { fRadius = val; }
    void SetLength(double val) { fLength = val; }

private:
    double fRadius = 12.6_cm;
    double fLength = 20_cm;
};
