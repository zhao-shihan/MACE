#pragma once

#include "Geometry/Interface/Entity.hxx"

class MACE::Geometry::Entity::Fast::SpectrometerReadoutLayers final :
    public MACE::Geometry::Interface::Entity {
public:
    SpectrometerReadoutLayers() = default;
    ~SpectrometerReadoutLayers() noexcept = default;
    SpectrometerReadoutLayers(const SpectrometerReadoutLayers&) = delete;
    SpectrometerReadoutLayers& operator=(const SpectrometerReadoutLayers&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};
