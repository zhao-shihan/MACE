#pragma once

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::VertexDetector final :
    public MACE::Geometry::Interface::Description {
public:
    static VertexDetector& Instance() noexcept;

private:
    VertexDetector() noexcept = default;
    ~VertexDetector() noexcept = default;
    VertexDetector(const VertexDetector&) = delete;
    VertexDetector& operator=(const VertexDetector&) = delete;

public:
    [[nodiscard]] const char* GetName()                   const override { return "VertexDetector"; }
    [[nodiscard]] const char* GetOverallDescription()     const override { return ""; }
    [[nodiscard]] const char* GetMaterialDescription()    const override { return ""; }
    [[nodiscard]] const char* GetShapeDescription()       const override { return ""; }
    [[nodiscard]] const char* GetMotherDescription()      const override { return ""; }
    [[nodiscard]] const char* GetTranslationDescription() const override { return ""; }
    [[nodiscard]] const char* GetRotationDescription()    const override { return ""; }

    [[nodiscard]] const auto& GetWidth()     const { return fWidth; }
    [[nodiscard]] const auto& GetThickness() const { return fThickness; }

    void SetWidth(double val) { fWidth = val; }
    void SetThickness(double val) { fThickness = val; }

private:
    double fWidth = 10_cm;
    double fThickness = 1_cm;
};
