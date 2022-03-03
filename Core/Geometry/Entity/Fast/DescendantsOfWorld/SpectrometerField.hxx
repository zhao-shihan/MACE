#pragma once

#include "Geometry/Interface/Entity.hxx"

class MACE::Geometry::Entity::Fast::SpectrometerField final :
    public MACE::Geometry::Interface::Entity {
public:
    SpectrometerField() = default;
    ~SpectrometerField() noexcept = default;
    SpectrometerField(const SpectrometerField&) = delete;
    SpectrometerField& operator=(const SpectrometerField&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};
