#pragma once

#include "Geometry/Interface/Entity.hxx"

class MACE::Geometry::Entity::Fast::SpectrometerFieldWires final :
    public MACE::Geometry::Interface::Entity {
public:
    SpectrometerFieldWires() = default;
    ~SpectrometerFieldWires() noexcept = default;
    SpectrometerFieldWires(const SpectrometerFieldWires&) = delete;
    SpectrometerFieldWires& operator=(const SpectrometerFieldWires&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};
