#pragma once

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::World final :
    public MACE::Geometry::Interface::Description {
public:
    static World& Instance() noexcept;

private:
    World() noexcept = default;
    ~World() noexcept = default;
    World(const World&) = delete;
    World& operator=(const World&) = delete;

public:
    [[nodiscard]] const char* GetName()                   const override { return "World"; }
    [[nodiscard]] const char* GetOverallDescription()     const override { return "The geometry world."; }
    [[nodiscard]] const char* GetMaterialDescription()    const override { return "Vacuum (of air). A properly defined pressure/density is recommended."; }
    [[nodiscard]] const char* GetShapeDescription()       const override { return "A big box that can contain everything."; }
    [[nodiscard]] const char* GetMotherDescription()      const override { return "Void."; }
    [[nodiscard]] const char* GetTranslationDescription() const override { return "No translation."; }
    [[nodiscard]] const char* GetRotationDescription()    const override { return "No rotation."; }

    [[nodiscard]] const auto& GetHalfXExtent() const { return fHalfXExtent; }
    [[nodiscard]] const auto& GetHalfYExtent() const { return fHalfYExtent; }
    [[nodiscard]] const auto& GetHalfZExtent() const { return fHalfZExtent; }

    void SetHalfXExtent(double val) { fHalfXExtent = val; }
    void SetHalfYExtent(double val) { fHalfYExtent = val; }
    void SetHalfZExtent(double val) { fHalfZExtent = val; }

private:
    double fHalfXExtent = 3_m;
    double fHalfYExtent = 1_m;
    double fHalfZExtent = 4_m;
};
