#pragma once

#include "Core/Geometry/Entity/IEntity.hxx"

namespace MACE::Geometry::Entity::Fast {

class CalorimeterField final : public IEntity {
public:
    CalorimeterField() = default;
    ~CalorimeterField() noexcept = default;
    CalorimeterField(const CalorimeterField&) = delete;
    CalorimeterField& operator=(const CalorimeterField&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};

} // namespace MACE::Geometry::Entity::Fast
