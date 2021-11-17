#pragma once

#include "Geometry/Interface/Description.hh"

class MACE::Geometry::Description::DescendantsOfWorld::DescendantsOfSpectrometerField::DescendantsOfAcceleratorField::Target :
    public MACE::Geometry::Interface::Description {
public:
    virtual ~Target() {}

    const char* GetName()                   const final override { return "Target"; }
    bool        IsComposedOfMultiVolume()   const final override { return false; }
    const char* GetMaterialDescription()    const final override { return "Silica aerogel."; }
    const char* GetShapeDescription()       const final override { return "A box with certain width(along XY) and thickness(along Z)."; }
    const char* GetMotherDescription()      const final override { return "AcceleratorField"; }
    const char* GetTranslationDescription() const final override { return "Downstream surface at z=0. (Be aware of AcceleratorField's position)"; }
    const char* GetRotationDescription()    const final override { return "No rotation."; }

    void SetWidth(double val) { fWidth = val; }
    void SetThickness(double val) { fThickness = val; }
    void SetDownZPosition(double val) { fDownZPosition = val; }

protected:
    double fWidth = 50_mm;
    double fThickness = 10_mm;
    double fDownZPosition = -13_cm;
};