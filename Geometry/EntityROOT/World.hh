#pragma once

#include "Geometry/Description/World.hh"
#include "Geometry/Interface/EntityROOT.hh"

class MACE::Geometry::EntityROOT::World final :
    public MACE::Geometry::Description::World,
    public MACE::Geometry::Interface::EntityROOT {
public:
    using EntityROOT::CreateSelfAndDescendants;

private:
    void CreateSelf() override {
        auto material = new TGeoMixture("Vacuum", 3);
        material->SetState(TGeoMaterial::kMatStateGas);
        material->AddElement(fgElementTable->FindElement("N"), 0.7809);
        material->AddElement(fgElementTable->FindElement("O"), 0.2095);
        material->AddElement(fgElementTable->FindElement("AR"), 0.0096);
        material->SetPressure(0.1_Pa);
        auto medium = new TGeoMedium("Vacuum", 1, material);

        fVolumes.emplace_back(fgGeoManager->MakeBox("World", medium, fHalfXExtent, fHalfYExtent, fHalfZExtent));
    }
};