#pragma once

#include "Geometry/Interface/Entity.hxx"

class MACE::Geometry::Entity::Fast::CalorimeterShield final :
    public MACE::Geometry::Interface::Entity {
public:
    CalorimeterShield() = default;
    ~CalorimeterShield() noexcept = default;
    CalorimeterShield(const CalorimeterShield&) = delete;
    CalorimeterShield& operator=(const CalorimeterShield&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};
