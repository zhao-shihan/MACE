#pragma once

#include "Geometry/Interface/Entity.hxx"

class MACE::Geometry::Entity::Fast::SpectrometerMagnet final :
    public MACE::Geometry::Interface::Entity {
public:
    SpectrometerMagnet() = default;
    ~SpectrometerMagnet() noexcept = default;
    SpectrometerMagnet(const SpectrometerMagnet&) = delete;
    SpectrometerMagnet& operator=(const SpectrometerMagnet&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};
