#pragma once

#include "Geometry/Interface/Description.hxx"

class MACE::Geometry::Description::World final :
    public MACE::Geometry::Interface::Description {
public:
    static World& Instance();

private:
    World() noexcept {}
    ~World() noexcept {}
    World(const World&) = delete;
    World& operator=(const World&) = delete;

public:
    const char* GetName()                   const override { return "World"; }
    const char* GetOverallDescription()     const override { return "The geometry world."; }
    const char* GetMaterialDescription()    const override { return "Vacuum (of air). A properly defined pressure/density is recommended."; }
    const char* GetShapeDescription()       const override { return "A big box that can contain everything."; }
    const char* GetMotherDescription()      const override { return "Void."; }
    const char* GetTranslationDescription() const override { return "No translation."; }
    const char* GetRotationDescription()    const override { return "No rotation."; }

    const auto& GetHalfXExtent() const { return fHalfXExtent; }
    const auto& GetHalfYExtent() const { return fHalfYExtent; }
    const auto& GetHalfZExtent() const { return fHalfZExtent; }

    void SetHalfXExtent(double val) { fHalfXExtent = val; }
    void SetHalfYExtent(double val) { fHalfYExtent = val; }
    void SetHalfZExtent(double val) { fHalfZExtent = val; }

private:
    double fHalfXExtent = 3_m;
    double fHalfYExtent = 1_m;
    double fHalfZExtent = 4_m;
};
