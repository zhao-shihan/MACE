#pragma once

#include "Core/Geometry/IEntity.hxx"

namespace MACE::Core::Geometry::Entity::Fast {

class CalorimeterShield final : public IEntity {
public:
    CalorimeterShield() = default;
    ~CalorimeterShield() noexcept = default;
    CalorimeterShield(const CalorimeterShield&) = delete;
    CalorimeterShield& operator=(const CalorimeterShield&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};

} // namespace MACE::Core::Geometry::Entity::Fast
