#pragma once

#include "Geometry/Interface/Entity.hxx"

class MACE::Geometry::Entity::Fast::VertexDetectorShield final :
    public MACE::Geometry::Interface::Entity {
public:
    VertexDetectorShield() = default;
    ~VertexDetectorShield() noexcept = default;
    VertexDetectorShield(const VertexDetectorShield&) = delete;
    VertexDetectorShield& operator=(const VertexDetectorShield&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};
