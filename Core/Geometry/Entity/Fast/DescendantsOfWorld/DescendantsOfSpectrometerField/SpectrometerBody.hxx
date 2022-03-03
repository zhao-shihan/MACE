#pragma once

#include "Geometry/Interface/Entity.hxx"

class MACE::Geometry::Entity::Fast::SpectrometerBody final :
    public MACE::Geometry::Interface::Entity {
public:
    SpectrometerBody() = default;
    ~SpectrometerBody() noexcept = default;
    SpectrometerBody(const SpectrometerBody&) = delete;
    SpectrometerBody& operator=(const SpectrometerBody&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};
