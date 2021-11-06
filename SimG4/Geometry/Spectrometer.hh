#pragma once

#include "SimG4/Global.hh"

#include "BaseInterface.hh"

class MACE::SimG4::Geometry::Spectrometer : virtual public MACE::SimG4::Geometry::BaseInterface {
public:
    Spectrometer();
    ~Spectrometer();

    void Create(G4Material* material, const BaseInterface* mother) override;

    void SetInnerRadius(G4double val) { fGasInnerRadius = val; }
    void SetOuterRadius(G4double val) { fGasOuterRadius = val; }
    void SetInnerLength(G4double val) { fGasInnerLength = val; }
    void SetOuterLength(G4double val) { fGasOuterLength = val; }

    void SetInnerThickness(G4double val) { fShellInnerThickness = val; }
    void SetSideThickness(G4double val) { fShellSideThickness = val; }
    void SetOuterThickness(G4double val) { fShellOuterThickness = val; }

protected:
    G4double fGasInnerRadius = 8 * cm;
    G4double fGasOuterRadius = 32 * cm;
    G4double fGasInnerLength = 19 * cm;
    G4double fGasOuterLength = 81 * cm;

    G4double fShellInnerThickness = 0.2 * mm;
    G4double fShellSideThickness = 5 * mm;
    G4double fShellOuterThickness = 10 * mm;
};
