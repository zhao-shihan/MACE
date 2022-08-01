#pragma once

#include "MACE/Core/Geometry/IEntity.hxx"

namespace MACE::Core::Geometry::Entity::Fast {

class LinacField final : public IEntity {
public:
    LinacField() = default;
    ~LinacField() noexcept = default;
    LinacField(const LinacField&) = delete;
    LinacField& operator=(const LinacField&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};

} // namespace MACE::Core::Geometry::Entity::Fast
