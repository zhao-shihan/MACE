#pragma once

#include "Core/Geometry/IDescription.hxx"

#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"

#include <cmath>

namespace MACE::Core::Geometry::Description {

class AcceleratorField final : public IDescription {
public:
    static AcceleratorField& Instance() noexcept;

private:
    AcceleratorField() = default;
    ~AcceleratorField() noexcept = default;
    AcceleratorField(const AcceleratorField&) = delete;
    AcceleratorField& operator=(const AcceleratorField&) = delete;

public:
    std::string GetName() const override { return "AcceleratorField"; }
    std::string GetOverallDescription() const override { return "An accelerator field box inside spectrometer"; }
    std::string GetMaterialDescription() const override { return "Vacuum."; }
    std::string GetShapeDescription() const override { return "A box with certain Width(along XY), UpStreamLength(length of z<0), and DownStreamLength(length of z>0)."; }
    std::string GetMotherDescription() const override { return "SpectrometerField"; }
    std::string GetTranslationDescription() const override { return "Translation should ensure the center z position satisifies shape description (see above)."; }
    std::string GetRotationDescription() const override { return "No rotation."; }

    const auto& GetRadius() const { return fRadius; }
    const auto& GetLength() const { return fLength; }
    const auto& GetDownStreamLength() const { return fDownStreamLength; }
    G4Transform3D GetTransform() const;

    void SetRadius(double val) { fRadius = val; }
    void SetLength(double val) { fLength = val; }
    void SetDownStreamLength(double val) { fDownStreamLength = val; }

private:
    double fRadius = 75_mm;
    double fLength = 100_cm;
    double fDownStreamLength = 90_cm;
};

} // namespace MACE::Core::Geometry::Description
