#pragma once

#include <memory>

#include "Geometry/Global.hh"

class MACE::Geometry::Interface::Entity {
public:
    Entity();
    Entity(const Entity&) = delete;
    virtual ~Entity() { delete fVolume; }

    void SetMother(Entity* mother);

    auto* GetVolume() const { return fVolume; }

protected:
    void CreateWholeFamily();

private:
    virtual void CreateSelf() = 0;

protected:
    Entity* fMother;
    TGeoVolume* fVolume;
    std::vector<Entity*> fDaughters;

    static TGeoManager* fgGeoManager;
    static TGeoElementTable* fgElementTable;
};