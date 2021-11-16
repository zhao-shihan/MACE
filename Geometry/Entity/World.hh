#pragma once

#include "Geometry/Interface/Entity.hh"

class MACE::Geometry::Entity::World final :
    public MACE::Geometry::Interface::Entity {
public:
    void SetHalfXExtent(Double_t val) { fHalfXExtent = val; }
    void SetHalfYExtent(Double_t val) { fHalfYExtent = val; }
    void SetHalfZExtent(Double_t val) { fHalfZExtent = val; }

    using Entity::CreateWholeFamily;

private:
    void CreateSelf() override;

private:
    Double_t fHalfXExtent = 3 * m;
    Double_t fHalfYExtent = 1 * m;
    Double_t fHalfZExtent = 4 * m;
};