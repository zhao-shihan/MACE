#pragma once

#include <iostream>

#include "Geometry/Global.hh"

class MACE::Geometry::Interface::Description {
public:
    Description() {}
    virtual ~Description() {}
    Description(const Description&) = delete;
    Description& operator=(const Description&) = delete;

    virtual const char* GetName()                   const = 0;
    virtual bool        IsComposedOfMultiVolume()   const = 0;
    virtual const char* GetMaterialDescription()    const = 0;
    virtual const char* GetShapeDescription()       const = 0;
    virtual const char* GetMotherDescription()      const = 0;
    virtual const char* GetTranslationDescription() const = 0;
    virtual const char* GetRotationDescription()    const = 0;
    virtual const char* GetOtherDescription()       const { return "None."; }

    friend std::ostream& operator<<(std::ostream& out, const Description& geomDescp);
};