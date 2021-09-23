#pragma once

#include "SimG4Global.hh"

#include "BaseInterface.hh"

class MACE::SimG4::Geometry::SpectrometerReadOutLayer final : public MACE::SimG4::Geometry::BaseInterface {
public:
    SpectrometerReadOutLayer();
    ~SpectrometerReadOutLayer();

    void Create(G4Material* material, const BaseInterface* mother) override;

    void SetReadOutPitch(G4double val) { fLayerPitch = val; }

private:
    G4double fLayerPitch = 15 * mm;
};