#pragma once

#include "Geometry/Interface/Entity.hxx"

class MACE::Geometry::Entity::Fast::SpectrometerShield final :
    public MACE::Geometry::Interface::Entity {
public:
    SpectrometerShield() = default;
    ~SpectrometerShield() noexcept = default;
    SpectrometerShield(const SpectrometerShield&) = delete;
    SpectrometerShield& operator=(const SpectrometerShield&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};
