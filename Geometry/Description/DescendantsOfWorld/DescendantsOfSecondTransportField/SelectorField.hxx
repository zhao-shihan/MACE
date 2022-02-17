#pragma once

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::SelectorField final :
    public MACE::Geometry::Interface::Description {
public:
    static SelectorField& Instance() noexcept;

private:
    SelectorField() noexcept = default;
    ~SelectorField() noexcept = default;
    SelectorField(const SelectorField&) = delete;
    SelectorField& operator=(const SelectorField&) = delete;

public:
    [[nodiscard]] const char* GetName()                   const override { return "SelectorField"; }
    [[nodiscard]] const char* GetOverallDescription()     const override { return ""; }
    [[nodiscard]] const char* GetMaterialDescription()    const override { return ""; }
    [[nodiscard]] const char* GetShapeDescription()       const override { return ""; }
    [[nodiscard]] const char* GetMotherDescription()      const override { return ""; }
    [[nodiscard]] const char* GetTranslationDescription() const override { return ""; }
    [[nodiscard]] const char* GetRotationDescription()    const override { return ""; }

    [[nodiscard]] const auto& GetRaidus()    const { return fRadius; }
    [[nodiscard]] const auto& GetLength()    const { return fLength; }
    [[nodiscard]] const auto& GetZPosition() const { return fZPosition; }

    void SetRaidus(double val) { fRadius = val; }
    void SetLength(double val) { fLength = val; }
    void SetZPosition(double val) { fZPosition = val; }

private:
    double fRadius = 10_cm;
    double fLength = 30_cm;
    double fZPosition = 20_cm;
};
