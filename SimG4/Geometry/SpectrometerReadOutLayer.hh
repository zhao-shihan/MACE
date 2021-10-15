#pragma once

#include "SimG4/Global.hh"

#include "BaseInterface.hh"
#include "SimG4/Geometry/Spectrometer.hh"

class MACE::SimG4::Geometry::SpectrometerReadOutLayer final : public MACE::SimG4::Geometry::Spectrometer {
public:
    SpectrometerReadOutLayer();
    ~SpectrometerReadOutLayer();

    void Create(G4Material* material, const BaseInterface* mother) override;

    void SetReadOutLayerPitch(G4double val) { fReadOutLayerPitch = val; }

private:
    G4double fReadOutLayerPitch = 15 * mm;
};