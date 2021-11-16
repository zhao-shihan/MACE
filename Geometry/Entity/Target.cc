#include "Geometry/Entity/Target.hh"

using namespace MACE::Geometry::Entity;

void Target::CreateSelf() {
    auto material = new TGeoMixture("Aerogel", 2);
    material->SetState(TGeoMaterial::kMatStateSolid);
    material->AddElement(fgElementTable->FindElement("SI"), 1);
    material->AddElement(fgElementTable->FindElement("O"), 2);
    material->SetDensity(30 * mg / cm3);
    auto medium = new TGeoMedium("Aerogel", 1, material);

    fVolume = fgGeoManager->MakeBox("Target", medium, 0.5 * fWidth, 0.5 * fWidth, 0.5 * fThickness);

    auto translation = new TGeoTranslation(0.0, 0.0, fDownZPosition);
    fMother->GetVolume()->AddNode(fVolume, 0, translation);
}