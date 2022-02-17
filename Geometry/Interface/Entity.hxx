#pragma once

#include <vector>
#include <memory>

#include "Geometry/Global.hxx"

template<class Volume_t>
class MACE::Geometry::Interface::Entity :
    public std::enable_shared_from_this<MACE::Geometry::Interface::Entity<Volume_t>> {
public:
    Entity();
    virtual ~Entity() noexcept;
    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;

    void AddDaughter(const std::shared_ptr<Entity>& daughter);
    void ConstructSelfAndDescendants();
    [[nodiscard]] Volume_t* GetVolume() const { return fVolumes.front(); }
    [[nodiscard]] Volume_t* GetVolume(size_t i) const { return fVolumes.at(i); }
    [[nodiscard]] auto GetVolumeNum() const { return fVolumes.size(); }

protected:
    std::shared_ptr<const Entity> Mother() const { return fMother.lock(); }

private:
    virtual void ConstructSelf() = 0;

protected:
    std::vector<Volume_t*> fVolumes;

private:
    std::weak_ptr<Entity> fMother;
    std::vector<std::shared_ptr<Entity>> fDaughters;
};

#include "Geometry/Interface/Entity.ixx"
