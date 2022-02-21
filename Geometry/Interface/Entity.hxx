#pragma once

#include <vector>
#include <memory>

#include "G4VSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"

#include "Geometry/Global.hxx"
#include "Utility/ObserverPtr.hxx"

class MACE::Geometry::Interface::Entity :
    public std::enable_shared_from_this<MACE::Geometry::Interface::Entity> {
public:
    Entity();
    virtual ~Entity() noexcept = default;
    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;

    void AddDaughter(const std::shared_ptr<Entity>& daughter);
    void ConstructSelfAndDescendants(G4bool checkOverlaps);
    [[nodiscard]] auto GetPhysicalVolumeNum() const { return fPhysicalVolumes.size(); }
    [[nodiscard]] auto GetPhysicalVolume(size_t volumeIndex = 0) const { return fPhysicalVolumes.at(volumeIndex).get(); }
    [[nodiscard]] auto GetLogicalVolume(size_t volumeIndex = 0) const { return GetPhysicalVolume(volumeIndex)->GetLogicalVolume(); }
    [[nodiscard]] auto GetSolid(size_t volumeIndex = 0) const { return GetLogicalVolume(volumeIndex)->GetSolid(); }
    void WriteSelfAndDesendentsToGDML(std::string_view fileName, size_t volumeIndex = 0) const;

protected:
    // Make a G4Solid and keep it (just for deleting when Entity deconstructs).
    template<class Solid_t, typename... Args>
    std::enable_if_t<std::is_base_of_v<G4VSolid, Solid_t>,
        ObserverPtr<Solid_t>> Make(Args&&... args);
    // Make a G4LogicalVolume and keep it (just for deleting when Entity deconstructs).
    template<class Logical_t, typename... Args>
    std::enable_if_t<std::is_base_of_v<G4LogicalVolume, Logical_t>,
        ObserverPtr<Logical_t>> Make(Args&&... args);
    // Make a G4PhysicalVolume and keep it for futher access. Will be deleted when Entity deconstructed.
    template<class Physical_t, typename... Args>
    std::enable_if_t<std::is_base_of_v<G4VPhysicalVolume, Physical_t>,
        ObserverPtr<Physical_t>> Make(Args&&... args);
    // shared_ptr points to the mother Entity.
    auto Mother() const { return std::static_pointer_cast<const Entity>(fMother); }

private:
    virtual void ConstructSelf(G4bool checkOverlaps) = 0;

private:
    std::shared_ptr<Entity>                         fMother;
    std::vector<std::weak_ptr<Entity>>              fDaughters;

    std::vector<std::unique_ptr<G4VSolid>>          fSolidStore;
    std::vector<std::unique_ptr<G4LogicalVolume>>   fLogicalVolumeStore;
    std::vector<std::unique_ptr<G4VPhysicalVolume>> fPhysicalVolumes;
};

#include "Geometry/Interface/Entity.ixx"
