#include "Geometry/Entity/World.hh"

using namespace MACE::Geometry::Entity;

void World::CreateSelf() {
    auto material = new TGeoMixture("Vacuum", 3);
    material->SetState(TGeoMaterial::kMatStateGas);
    material->AddElement(fgElementTable->FindElement("N"), 0.7809);
    material->AddElement(fgElementTable->FindElement("O"), 0.2095);
    material->AddElement(fgElementTable->FindElement("AR"), 0.0096);
    material->SetPressure(0.1 * pascal);
    auto medium = new TGeoMedium("Vacuum", 1, material);

    fVolume = fgGeoManager->MakeBox("World", medium, fHalfXExtent, fHalfYExtent, fHalfZExtent);
}