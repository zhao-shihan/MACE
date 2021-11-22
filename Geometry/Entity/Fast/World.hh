#pragma once

#include "Geometry/Description/World.hh"
#include "Geometry/Interface/EntityROOT.hh"

class MACE::Geometry::Entity::Fast::World final :
    public MACE::Geometry::Interface::EntityROOT<MACE::Geometry::Description::World> {
    void CreateSelf() override {
        auto material = new TGeoMixture("Vacuum", 3);
        material->SetState(TGeoMaterial::kMatStateGas);
        material->AddElement(fgElementTable->FindElement("N"), 0.7809);
        material->AddElement(fgElementTable->FindElement("O"), 0.2095);
        material->AddElement(fgElementTable->FindElement("AR"), 0.0096);
        material->SetPressure(0.1_Pa);
        auto medium = new TGeoMedium("Vacuum", 1, material);

        auto name = GetDescription()->GetName();
        auto halfX = GetDescription()->GetHalfXExtent();
        auto halfY = GetDescription()->GetHalfYExtent();
        auto halfZ = GetDescription()->GetHalfZExtent();
        fVolumes.emplace_back(fgGeoManager->MakeBox(name, medium, halfX, halfY, halfZ));
    }

public:
    using EntityROOT::CreateSelfAndDescendants;
};