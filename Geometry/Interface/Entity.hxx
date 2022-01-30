#pragma once

#include <vector>

#include "Geometry/Global.hxx"

template<class Volume_t>
class MACE::Geometry::Interface::Entity {
protected:
    Entity();
    virtual ~Entity();
    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;

public:
    void AddDaughter(Entity* daughter);
    void ConstructSelfAndDescendants();
    Volume_t* GetVolume() const { return fVolumes.front(); }
    Volume_t* GetVolume(size_t i) const { return fVolumes.at(i); }
    auto GetVolumeNum() const { return fVolumes.size(); }

protected:
    const Entity* Mother() const { return fMother; }

private:
    virtual void ConstructSelf() = 0;

protected:
    std::vector<Volume_t*> fVolumes;

private:
    Entity* fMother;
    std::vector<Entity*> fDaughters;
};

#include "Geometry/Interface/Entity.txx"