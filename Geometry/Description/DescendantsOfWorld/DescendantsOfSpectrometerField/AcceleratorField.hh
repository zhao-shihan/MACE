#pragma once

#include "Geometry/Interface/Description.hh"

class MACE::Geometry::Description::DescendantsOfWorld::DescendantsOfSpectrometerField::AcceleratorField :
    public MACE::Geometry::Interface::Description {
public:
    virtual ~AcceleratorField() {}

    const char* GetName()                   const final override { return "AcceleratorField"; }
    bool        IsComposedOfMultiVolume()   const final override { return false; }
    const char* GetMaterialDescription()    const final override { return "Vacuum."; }
    const char* GetShapeDescription()       const final override { return "A box with certain Width(along XY), UpStreamLength(length of z<0), and DownStreamLength(length of z>0)."; }
    const char* GetMotherDescription()      const final override { return "SpectrometerField"; }
    const char* GetTranslationDescription() const final override { return "Translation should ensure the center z position satisifies shape description (see above)."; }
    const char* GetRotationDescription()    const final override { return "No rotation."; }

    void SetWidth(double val) { fWidth = val; }
    void SetUpStreamLength(double val) { fUpStreamLength = val; }
    void SetDownStreamLength(double val) { fDownStreamLength = val; }

protected:
    double fWidth = M_SQRT2 * 7_cm;
    double fUpStreamLength = 4_cm;
    double fDownStreamLength = 30_cm;
};