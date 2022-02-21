#pragma once

#include "Geometry/Interface/Entity.hxx"

class MACE::Geometry::Entity::Fast::Collimator final :
    public MACE::Geometry::Interface::Entity {
public:
    Collimator() = default;
    ~Collimator() noexcept = default;
    Collimator(const Collimator&) = delete;
    Collimator& operator=(const Collimator&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};
