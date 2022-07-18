#pragma once

#include "MACE/Utility/ObserverPtr.hxx"

#include "G4EquationOfMotion.hh"
#include "G4Field.hh"
#include "G4LogicalVolume.hh"
#include "G4Region.hh"
#include "G4VIntegrationDriver.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VSensitiveDetector.hh"
#include "G4VSolid.hh"

#include <memory>
#include <vector>

namespace MACE::Core::Geometry {

using Utility::ObserverPtr;

class IEntity : public std::enable_shared_from_this<IEntity> {
public:
    IEntity();
    virtual ~IEntity() noexcept = default;
    IEntity(const IEntity&) = delete;
    IEntity& operator=(const IEntity&) = delete;

    /// @brief Determines whether we will construct this entity.
    /// Entities could override this function to control whether this will be constructed.
    /// A typical usage is to get the information of whether to enable this from description in the override function.
    virtual bool IsEnabled() const { return true; }

    void AddDaughter(const std::shared_ptr<IEntity>& daughter);
    void ConstructSelfAndDescendants(G4bool checkOverlaps);

    void RegisterMaterial(size_t volumeIndex, G4Material* region) const;
    void RegisterMaterial(G4Material* region) const;

    void RegisterRegion(size_t volumeIndex, G4Region* region) const;
    void RegisterRegion(G4Region* region) const;

    void RegisterSD(size_t volumeIndex, G4VSensitiveDetector* sd) const;
    void RegisterSD(G4VSensitiveDetector* sd) const;

    template<std::derived_from<G4Field> AField, std::derived_from<G4EquationOfMotion> AEquation, class AStepper, std::derived_from<G4VIntegrationDriver> ADriver>
    void RegisterField(size_t volumeIndex, AField* field, G4double hMin, G4int nVal, G4bool propagateToDescendants) const;
    template<std::derived_from<G4Field> AField, std::derived_from<G4EquationOfMotion> AEquation, class AStepper, std::derived_from<G4VIntegrationDriver> ADriver>
    void RegisterField(AField* field, G4double hMin, G4int nVal, G4bool propagateToDescendants) const;

#if MACE_WITH_G4GDML
    void WriteSelfAndDesendentsToGDML(std::string_view fileName, size_t volumeIndex = 0) const;
#endif

    auto GetLogicalVolumeNum() const { return fLogicalVolumes.size(); }
    auto GetLogicalVolume(size_t volumeIndex = 0) const { return fLogicalVolumes.at(volumeIndex).get(); }

    auto GetPhysicalVolumeNum() const { return fPhysicalVolumes.size(); }
    auto GetPhysicalVolume(size_t volumeIndex = 0) const { return fPhysicalVolumes.at(volumeIndex).get(); }

protected:
    // Make a G4Solid and keep it (just for deleting when Entity deconstructs).
    template<std::derived_from<G4VSolid> ASolid, typename... Args>
    ObserverPtr<ASolid> Make(Args&&... args);
    // Make a G4LogicalVolume and keep it for futher access. Will be deleted when Entity deconstructed.
    template<std::derived_from<G4LogicalVolume> ALogical, typename... Args>
    ObserverPtr<ALogical> Make(Args&&... args);
    // Make a G4PhysicalVolume and keep it for futher access. Will be deleted when Entity deconstructed.
    template<std::derived_from<G4VPhysicalVolume> APhysical, typename... Args>
    ObserverPtr<APhysical> Make(Args&&... args);

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

} // namespace MACE::Core::Geometry

#include "MACE/Core/Geometry/IEntity.inl"
