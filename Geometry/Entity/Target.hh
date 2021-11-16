#pragma once

#include "Geometry/Interface/Entity.hh"

class MACE::Geometry::Entity::Target final :
    public MACE::Geometry::Interface::Entity {
public:
    void SetWidth(Double_t val) { fWidth = val; }
    void SetThickness(Double_t val) { fThickness = val; }
    void SetDownZPosition(Double_t val) { fDownZPosition = val; }

private:
    void CreateSelf() override;

private:
    Double_t fWidth = 50 * mm;
    Double_t fThickness = 10 * mm;
    Double_t fDownZPosition = -130 * mm;
};