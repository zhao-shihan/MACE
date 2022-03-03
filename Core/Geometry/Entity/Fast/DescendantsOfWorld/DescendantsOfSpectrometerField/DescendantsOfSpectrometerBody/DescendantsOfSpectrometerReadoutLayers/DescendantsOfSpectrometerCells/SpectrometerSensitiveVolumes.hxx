#pragma once

#include "Geometry/Interface/Entity.hxx"

class MACE::Geometry::Entity::Fast::SpectrometerSensitiveVolumes final :
    public MACE::Geometry::Interface::Entity {
public:
    SpectrometerSensitiveVolumes() = default;
    ~SpectrometerSensitiveVolumes() noexcept = default;
    SpectrometerSensitiveVolumes(const SpectrometerSensitiveVolumes&) = delete;
    SpectrometerSensitiveVolumes& operator=(const SpectrometerSensitiveVolumes&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};
