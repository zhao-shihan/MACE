#include "Geometry/Interface/Entity.hh"

using namespace MACE::Geometry::Interface;

TGeoManager* Entity::fgGeoManager = nullptr;
TGeoElementTable* Entity::fgElementTable = nullptr;

Entity::Entity() :
    fMother(nullptr),
    fVolume(nullptr),
    fDaughters(0) {
    if (fgGeoManager == nullptr) {
        fgGeoManager = new TGeoManager("GeomMACE", "Geometry of MACE");
        TGeoManager::SetDefaultUnits(TGeoManager::kG4Units);
        TGeoManager::LockDefaultUnits(true);
    }
    if (fgElementTable == nullptr) {
        fgElementTable = new TGeoElementTable();
        fgElementTable->BuildDefaultElements();
    }
}

void Entity::SetMother(Entity* mother) {
    fMother = mother;
    mother->fDaughters.emplace_back(this);
}

void Entity::CreateWholeFamily() {
    this->CreateSelf();
    for (auto&& daughter : fDaughters) {
        daughter->CreateWholeFamily();
    }
}