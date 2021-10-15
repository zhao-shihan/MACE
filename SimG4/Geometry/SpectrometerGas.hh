#pragma once

#include "SimG4/Global.hh"

#include "BaseInterface.hh"
#include "SimG4/Geometry/Spectrometer.hh"

class MACE::SimG4::Geometry::SpectrometerGas final : public MACE::SimG4::Geometry::Spectrometer {
public:
    SpectrometerGas();
    ~SpectrometerGas();

    void Create(G4Material* material, const BaseInterface* mother) override;
};