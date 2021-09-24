#pragma once

#include "SimG4Global.hh"

#include "BaseInterface.hh"
#include "detector/geometry/Spectrometer.hh"

class MACE::SimG4::Geometry::SpectrometerGas final : public MACE::SimG4::Geometry::Spectrometer {
public:
    SpectrometerGas();
    ~SpectrometerGas();

    void Create(G4Material* material, const BaseInterface* mother) override;
};