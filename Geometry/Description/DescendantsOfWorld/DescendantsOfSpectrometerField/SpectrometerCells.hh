#pragma once

#include "Geometry/Interface/Description.hh"

class MACE::Geometry::Description::SpectrometerCells final :
    public MACE::Geometry::Interface::Description {
    MACE_GEOMETRY_DESCRIPTION_CONSTRAINT(SpectrometerCells);
public:
    const char* GetName()                   const override { return "SpectrometerCells"; }
    const char* GetOverallDescription()     const override { return "Sensitive cells of MWDC. The cell includes sense wires, field wires, and gas, respectively."; }
    const char* GetMaterialDescription()    const override { return "Carbon fiber."; }
    const char* GetShapeDescription()       const override { return "Wire: Cylinders. Gas: A angular slice of tube."; }
    const char* GetMotherDescription()      const override { return "SpectrometerField"; }
    const char* GetTranslationDescription() const override { return "Depending on the implementation."; }
    const char* GetRotationDescription()    const override { return "Depending on the implementation."; }
};