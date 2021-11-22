#pragma once

#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfAcceleratorField/Target.hh"
#include "Geometry/Interface/EntityROOT.hh"

class MACE::Geometry::Entity::Fast::Target final :
    public MACE::Geometry::Interface::EntityROOT<MACE::Geometry::Description::Target> {
    void CreateSelf() override {
        auto material = new TGeoMixture("Aerogel", 2);
        material->SetState(TGeoMaterial::kMatStateSolid);
        material->AddElement(fgElementTable->FindElement("SI"), 1);
        material->AddElement(fgElementTable->FindElement("O"), 2);
        material->SetDensity(30_mg_cm3);
        auto medium = new TGeoMedium("Aerogel", 1, material);

        auto name = GetDescription()->GetName();
        auto width = GetDescription()->GetWidth();
        auto thickness = GetDescription()->GetThickness();
        auto volume = fgGeoManager->MakeBox(name, medium, 0.5 * width, 0.5 * width, 0.5 * thickness);
        fVolumes.emplace_back(volume);

        auto downZPosition = GetDescription()->GetDownZPosition();
        auto translation = new TGeoTranslation(0.0, 0.0, downZPosition);
        fMother->GetVolume()->AddNode(volume, 0, translation);
    }
};