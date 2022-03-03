#pragma once

#include "Geometry/Interface/Entity.hxx"

class MACE::Geometry::Entity::Fast::VertexDetector final :
    public MACE::Geometry::Interface::Entity {
public:
    VertexDetector() = default;
    ~VertexDetector() noexcept = default;
    VertexDetector(const VertexDetector&) = delete;
    VertexDetector& operator=(const VertexDetector&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};
