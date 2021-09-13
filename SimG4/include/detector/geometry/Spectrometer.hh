#pragma once

#include "G4GDMLParser.hh"

#include "SimG4Global.hh"

#include "BaseInterface.hh"

class MACE::SimG4::Geometry::Spectrometer final : public MACE::SimG4::Geometry::BaseInterface {
public:
    Spectrometer();
    ~Spectrometer();

    void Create(G4Material* material, G4VPhysicalVolume* mother);

    void SetInnerRadius(G4double val) { fInnerRadius = val; }
    void SetOuterRadius(G4double val) { fOuterRadius = val; }
    void SetInnerEffectiveLength(G4double val) { fInnerEffectiveLength = val; }
    void SetOuterEffectiveLength(G4double val) { fOuterEffectiveLength = val; }
    void SetThickness(G4double val) { fThickness = val; }
    void SetCount(size_t count) { ResizeVolumeSetList(count); }

private:
    G4double fInnerRadius = 8.2 * cm;
    G4double fOuterRadius = 32 * cm;
    G4double fInnerEffectiveLength = 20 * cm;
    G4double fOuterEffectiveLength = 80 * cm;
    G4double fThickness = 1 * cm;

    G4GDMLParser* const fGDML;
};
