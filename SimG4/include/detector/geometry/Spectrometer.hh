#pragma once

#include "SimG4Global.hh"

#include "BaseInterface.hh"

class MACE::SimG4::Geometry::Spectrometer final : public MACE::SimG4::Geometry::BaseInterface {
public:
    Spectrometer();
    ~Spectrometer();

    void Create(G4Material* material, const BaseInterface* mother) override;

    auto GetInnerRadius() const { return fInnerRadius; }
    auto GetOuterRadius() const { return fOuterRadius; }
    auto GetInnerLength() const { return fInnerLength; }
    auto GetOuterLength() const { return fOuterLength; }
    
    void SetInnerRadius(G4double val) { fInnerRadius = val; }
    void SetOuterRadius(G4double val) { fOuterRadius = val; }
    void SetInnerLength(G4double val) { fInnerLength = val; }
    void SetOuterLength(G4double val) { fOuterLength = val; }

private:
    G4double fInnerRadius = 8.2 * cm;
    G4double fOuterRadius = 32 * cm;
    G4double fInnerLength = 19 * cm;
    G4double fOuterLength = 81 * cm;
};
