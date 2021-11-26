#pragma once

#include "Geometry/Interface/Description.hh"

class MACE::Geometry::Description::SpectrometerCells final :
    public MACE::Geometry::Interface::Description {
    MACE_GEOMETRY_DESCRIPTION_CONSTRAINT(SpectrometerCells);
public:
    const char* GetName()                   const override { return "SpectrometerCells"; }
    const char* GetOverallDescription()     const override { return "Sensitive cells of MWDC. The cell's full geometry includes sense wires, field wires, and gas, respectively. Fast geometry may exclude wires."; }
    const char* GetMaterialDescription()    const override { return "Gas: He-based gas. Wires: respect to BESIII currently."; }
    const char* GetShapeDescription()       const override { return "Wire: Cylinders. Gas: A angular slice of tube."; }
    const char* GetMotherDescription()      const override { return "SpectrometerField"; }
    const char* GetTranslationDescription() const override { return "Depending on the implementation."; }
    const char* GetRotationDescription()    const override { return "Depending on the implementation."; }

    auto GetAverageCellWidth() const { return fAverageCellWidth; }

    void SetAverageCellWidth(double val) { fAverageCellWidth = val; }

private:
    double fAverageCellWidth = 1_cm;
};