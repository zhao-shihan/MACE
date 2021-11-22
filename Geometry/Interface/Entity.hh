#pragma once

#include <vector>

#include "Geometry/Global.hh"

template<class VolumeType>
class MACE::Geometry::Interface::Entity {
protected:
    Entity();
    virtual ~Entity();
    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;

public:
    void AddDaughter(Entity* daughter);
    VolumeType* GetVolume() const { return fVolumes.front(); }
    VolumeType* GetVolume(size_t i) const { return fVolumes.at(i); }

protected:
    void CreateSelfAndDescendants();

private:
    virtual void CreateSelf() = 0;

protected:
    Entity* fMother;
    std::vector<VolumeType*> fVolumes;

private:
    std::vector<Entity*> fDaughters;
};

#include "Geometry/Interface/Entity.tcc"