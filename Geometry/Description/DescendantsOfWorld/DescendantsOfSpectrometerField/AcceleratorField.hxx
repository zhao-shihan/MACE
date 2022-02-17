#pragma once

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
    [[nodiscard]] const char* GetName()                   const override { return "AcceleratorField"; }
    [[nodiscard]] const char* GetOverallDescription()     const override { return "An accelerator field box inside spectrometer"; }
    [[nodiscard]] const char* GetMaterialDescription()    const override { return "Vacuum."; }
    [[nodiscard]] const char* GetShapeDescription()       const override { return "A box with certain Width(along XY), UpStreamLength(length of z<0), and DownStreamLength(length of z>0)."; }
    [[nodiscard]] const char* GetMotherDescription()      const override { return "SpectrometerField"; }
    [[nodiscard]] const char* GetTranslationDescription() const override { return "Translation should ensure the center z position satisifies shape description (see above)."; }
    [[nodiscard]] const char* GetRotationDescription()    const override { return "No rotation."; }

    [[nodiscard]] const auto& GetWidth() const { return fWidth; }
    [[nodiscard]] const auto& GetUpStreamLength() const { return fUpStreamLength; }
    [[nodiscard]] const auto& GetDownStreamLength() const { return fDownStreamLength; }

    void SetWidth(double val) { fWidth = val; }
    void SetUpStreamLength(double val) { fUpStreamLength = val; }
    void SetDownStreamLength(double val) { fDownStreamLength = val; }

private:
    double fWidth = M_SQRT2 * 7_cm;
    double fUpStreamLength = 4_cm;
    double fDownStreamLength = 30_cm;
};
