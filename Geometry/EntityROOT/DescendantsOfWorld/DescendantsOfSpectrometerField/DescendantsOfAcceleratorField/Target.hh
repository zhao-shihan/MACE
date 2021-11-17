#pragma once

#include "Geometry/Interface/EntityROOT.hh"
#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfAcceleratorField/Target.hh"

class MACE::Geometry::EntityROOT::DescendantsOfWorld::DescendantsOfSpectrometerField::DescendantsOfAcceleratorField::Target final :
    public MACE::Geometry::Description::DescendantsOfWorld::DescendantsOfSpectrometerField::DescendantsOfAcceleratorField::Target,
    public MACE::Geometry::Interface::EntityROOT {
    void CreateSelf() override {
        auto material = new TGeoMixture("Aerogel", 2);
        material->SetState(TGeoMaterial::kMatStateSolid);
        material->AddElement(fgElementTable->FindElement("SI"), 1);
        material->AddElement(fgElementTable->FindElement("O"), 2);
        material->SetDensity(30_mg_cm3);
        auto medium = new TGeoMedium("Aerogel", 1, material);

        auto volume = fgGeoManager->MakeBox("Target", medium, 0.5 * fWidth, 0.5 * fWidth, 0.5 * fThickness);
        fVolumes.emplace_back(volume);

        auto translation = new TGeoTranslation(0.0, 0.0, fDownZPosition);
        fMother->GetVolume()->AddNode(volume, 0, translation);
    }
};