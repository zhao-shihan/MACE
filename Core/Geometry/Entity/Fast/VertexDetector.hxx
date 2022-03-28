#pragma once

#include "Core/Geometry/IEntity.hxx"

namespace MACE::Geometry::Entity::Fast {

class VertexDetector final : public IEntity {
public:
    VertexDetector() = default;
    ~VertexDetector() noexcept = default;
    VertexDetector(const VertexDetector&) = delete;
    VertexDetector& operator=(const VertexDetector&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};

} // namespace MACE::Geometry::Entity::Fast
