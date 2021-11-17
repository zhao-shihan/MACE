#pragma once

#include "Geometry/Interface/Description.hh"

class MACE::Geometry::Description::World :
    public MACE::Geometry::Interface::Description {
public:
    virtual ~World() {}

    const char* GetName()                   const final override { return "World"; }
    bool        IsComposedOfMultiVolume()   const final override { return false; }
    const char* GetMaterialDescription()    const final override { return "Vacuum (of air). A properly defined pressure/density is recommended."; }
    const char* GetShapeDescription()       const final override { return "A big box that can contain everything."; }
    const char* GetMotherDescription()      const final override { return "Void."; }
    const char* GetTranslationDescription() const final override { return "No translation."; }
    const char* GetRotationDescription()    const final override { return "No rotation."; }

    void SetHalfXExtent(double val) { fHalfXExtent = val; }
    void SetHalfYExtent(double val) { fHalfYExtent = val; }
    void SetHalfZExtent(double val) { fHalfZExtent = val; }

protected:
    double fHalfXExtent = 3_m;
    double fHalfYExtent = 1_m;
    double fHalfZExtent = 4_m;
};