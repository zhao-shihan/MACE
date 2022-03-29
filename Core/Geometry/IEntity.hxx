#pragma once

#include "Utility/ObserverPtr.hxx"

#include "G4LogicalVolume.hh"
#include "G4Region.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VSensitiveDetector.hh"
#include "G4VSolid.hh"

#include <memory>
#include <vector>

namespace MACE::Geometry {

using Utility::ObserverPtr;

class IEntity : public std::enable_shared_from_this<IEntity> {
public:
    IEntity();
    virtual ~IEntity() noexcept = default;
    IEntity(const IEntity&) = delete;
    IEntity& operator=(const IEntity&) = delete;

    void AddDaughter(const std::shared_ptr<IEntity>& daughter);
    void ConstructSelfAndDescendants(G4bool checkOverlaps);

    void RegisterRegion(size_t volumeIndex, G4Region* region) const;
    void RegisterRegion(G4Region* region) const;

    void RegisterSD(size_t volumeIndex, G4VSensitiveDetector* sd) const;
    void RegisterSD(G4VSensitiveDetector* sd) const;

    template<class Field_t, class Equation_t, class Stepper_t, class Driver_t>
    void RegisterField(size_t volumeIndex, Field_t* field, G4double hMin, G4int nVal, G4bool propagateToDescendants) const;
    template<class Field_t, class Equation_t, class Stepper_t, class Driver_t>
    void RegisterField(Field_t* field, G4double hMin, G4int nVal, G4bool propagateToDescendants) const;

    void WriteSelfAndDesendentsToGDML(std::string_view fileName, size_t volumeIndex = 0) const;

    auto GetLogicalVolumeNum() const { return fLogicalVolumes.size(); }
    auto GetLogicalVolume(size_t volumeIndex = 0) const { return fLogicalVolumes.at(volumeIndex).get(); }
    auto&& GetLogicalVolumeName(size_t volumeIndex = 0) const { return GetLogicalVolume(volumeIndex)->GetName(); }
    auto GetMaterial(size_t volumeIndex = 0) const { return GetLogicalVolume(volumeIndex)->GetMaterial(); }

    auto GetPhysicalVolumeNum() const { return fPhysicalVolumes.size(); }
    auto GetPhysicalVolume(size_t volumeIndex = 0) const { return fPhysicalVolumes.at(volumeIndex).get(); }
    auto&& GetPhysicalVolumeName(size_t volumeIndex = 0) const { return GetPhysicalVolume(volumeIndex)->GetName(); }

protected:
    // Make a G4Solid and keep it (just for deleting when Entity deconstructs).
    template<class Solid_t, typename... Args>
    std::enable_if_t<std::derived_from<Solid_t, G4VSolid>, ObserverPtr<Solid_t>> Make(Args&&... args);
    // Make a G4LogicalVolume and keep it for futher access. Will be deleted when Entity deconstructed.
    template<class Logical_t, typename... Args>
    std::enable_if_t<std::derived_from<Logical_t, G4LogicalVolume>, ObserverPtr<Logical_t>> Make(Args&&... args);
    // Make a G4PhysicalVolume and keep it for futher access. Will be deleted when Entity deconstructed.
    template<class Physical_t, typename... Args>
    std::enable_if_t<std::derived_from<Physical_t, G4VPhysicalVolume>, ObserverPtr<Physical_t>> Make(Args&&... args);

    // shared_ptr points to the mother Entity.
    auto Mother() const { return std::const_pointer_cast<const IEntity>(fMother); }

private:
    virtual void ConstructSelf(G4bool checkOverlaps) = 0;

private:
    std::shared_ptr<IEntity> fMother;
    std::vector<std::weak_ptr<IEntity>> fDaughters;

    std::vector<std::unique_ptr<G4VSolid>> fSolidStore;
    std::vector<std::unique_ptr<G4LogicalVolume>> fLogicalVolumes;
    std::vector<std::unique_ptr<G4VPhysicalVolume>> fPhysicalVolumes;
};

} // namespace MACE::Geometry

#include "Core/Geometry/IEntity.ixx"
