#pragma once

#include "Geometry/Interface/Entity.hxx"

class MACE::Geometry::Entity::Fast::SpectrometerSenseWires final :
    public MACE::Geometry::Interface::Entity {
public:
    SpectrometerSenseWires() = default;
    ~SpectrometerSenseWires() noexcept = default;
    SpectrometerSenseWires(const SpectrometerSenseWires&) = delete;
    SpectrometerSenseWires& operator=(const SpectrometerSenseWires&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};
