#pragma once

#include "Geometry/Interface/Entity.hxx"

class MACE::Geometry::Entity::Fast::CalorimeterField final :
    public MACE::Geometry::Interface::Entity {
public:
    CalorimeterField() = default;
    ~CalorimeterField() noexcept = default;
    CalorimeterField(const CalorimeterField&) = delete;
    CalorimeterField& operator=(const CalorimeterField&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};
