#pragma once

#include "Geometry/Interface/Entity.hxx"

class MACE::Geometry::Entity::Fast::SpectrometerCells final :
    public MACE::Geometry::Interface::Entity {
public:
    SpectrometerCells() = default;
    ~SpectrometerCells() noexcept = default;
    SpectrometerCells(const SpectrometerCells&) = delete;
    SpectrometerCells& operator=(const SpectrometerCells&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};
