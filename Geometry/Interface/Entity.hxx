#pragma once

#include <vector>

#include "Geometry/Global.hxx"

template<class VolumeType>
class MACE::Geometry::Interface::Entity {
protected:
    Entity();
    virtual ~Entity();
    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;

public:
    void AddDaughter(Entity* daughter);
    void ConstructSelfAndDescendants();
    VolumeType* GetVolume() const { return fVolumes.front(); }
    VolumeType* GetVolume(size_t i) const { return fVolumes.at(i); }
    auto GetVolumeNum() const { return fVolumes.size(); }

protected:
    const auto* Mother() const { return fMother; }

private:
    virtual void ConstructSelf() = 0;

protected:
    std::vector<VolumeType*> fVolumes;

private:
    Entity* fMother;
    std::vector<Entity*> fDaughters;
};

#include "Geometry/Interface/Entity.txx"