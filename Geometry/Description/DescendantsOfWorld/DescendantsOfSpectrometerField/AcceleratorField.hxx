#pragma once

#include <cmath>

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::AcceleratorField final :
    public MACE::Geometry::Interface::Description {
public:
    static AcceleratorField& Instance() noexcept;

private:
    AcceleratorField() noexcept = default;
    ~AcceleratorField() noexcept = default;
    AcceleratorField(const AcceleratorField&) = delete;
    AcceleratorField& operator=(const AcceleratorField&) = delete;

public:
    [[nodiscard]] std::string GetName()                   const override { return "AcceleratorField"; }
    [[nodiscard]] std::string GetOverallDescription()     const override { return "An accelerator field box inside spectrometer"; }
    [[nodiscard]] std::string GetMaterialDescription()    const override { return "Vacuum."; }
    [[nodiscard]] std::string GetShapeDescription()       const override { return "A box with certain Width(along XY), UpStreamLength(length of z<0), and DownStreamLength(length of z>0)."; }
    [[nodiscard]] std::string GetMotherDescription()      const override { return "SpectrometerField"; }
    [[nodiscard]] std::string GetTranslationDescription() const override { return "Translation should ensure the center z position satisifies shape description (see above)."; }
    [[nodiscard]] std::string GetRotationDescription()    const override { return "No rotation."; }

    [[nodiscard]] const auto& GetRadius() const { return fRadius; }
    [[nodiscard]] const auto& GetLength() const { return fLength; }
    [[nodiscard]] const auto& GetDownStreamLength() const { return fDownStreamLength; }
    [[nodiscard]] auto        GetTransform() const { return G4Transform3D(G4RotationMatrix(), G4ThreeVector(0, 0, fDownStreamLength - fLength / 2)); }

    void SetRadius(double val) { fRadius = val; }
    void SetLength(double val) { fLength = val; }
    void SetDownStreamLength(double val) { fDownStreamLength = val; }

private:
    double fRadius = 5_cm;
    double fLength = 85_cm;
    double fDownStreamLength = 80_cm;
};
