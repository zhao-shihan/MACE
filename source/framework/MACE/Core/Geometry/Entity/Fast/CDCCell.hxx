#pragma once

#include "MACE/Core/Geometry/IEntity.hxx"

namespace MACE::Core::Geometry::Entity::Fast {

class CDCCell final : public IEntity {
public:
    CDCCell() = default;
    ~CDCCell() noexcept = default;
    CDCCell(const CDCCell&) = delete;
    CDCCell& operator=(const CDCCell&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};

} // namespace MACE::Core::Geometry::Entity::Fast
