#pragma once

#include "MACE/Utility/NonMoveableBase.hxx"

#include "G4EquationOfMotion.hh"
#include "G4Field.hh"
#include "G4LogicalVolume.hh"
#include "G4Region.hh"
#include "G4VIntegrationDriver.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VSensitiveDetector.hh"
#include "G4VSolid.hh"

#include "gsl/gsl"

#include <memory>
#include <vector>

#if MACE_USE_G4GDML
#    include <filesystem>
#endif

namespace MACE::Core::Geometry {

class IEntity : public Utility::NonMoveableBase,
                public std::enable_shared_from_this<IEntity> {
public:
    IEntity();
    virtual ~IEntity() = default;

    /// @brief Determines whether we will construct this entity.
    /// Entities could override this function to control whether this will be constructed.
    /// A typical usage is to get the information of whether to enable this from description in the override function.
    virtual bool Enabled() const { return true; }

    void AddDaughter(const std::shared_ptr<IEntity>& daughter);
    void ConstructSelfAndDescendants(G4bool checkOverlaps);

    void RegisterMaterial(gsl::index volumeIndex, gsl::not_null<G4Material*> material) const;
    void RegisterMaterial(gsl::not_null<G4Material*> material) const;

    void RegisterRegion(gsl::index volumeIndex, gsl::not_null<G4Region*> region) const;
    void RegisterRegion(gsl::not_null<G4Region*> region) const;

    void RegisterSD(gsl::index volumeIndex, gsl::not_null<G4VSensitiveDetector*> sd) const;
    void RegisterSD(gsl::not_null<G4VSensitiveDetector*> sd) const;

    template<std::derived_from<G4Field> AField, std::derived_from<G4EquationOfMotion> AEquation, class AStepper, std::derived_from<G4VIntegrationDriver> ADriver>
    void RegisterField(gsl::index volumeIndex, gsl::not_null<AField*> field, G4double hMin, G4int nVal, G4bool propagateToDescendants) const;
    template<std::derived_from<G4Field> AField, std::derived_from<G4EquationOfMotion> AEquation, class AStepper, std::derived_from<G4VIntegrationDriver> ADriver>
    void RegisterField(gsl::not_null<AField*> field, G4double hMin, G4int nVal, G4bool propagateToDescendants) const;

#if MACE_USE_G4GDML
    void Export(std::filesystem::path gdmlFile, gsl::index volumeIndex = 0) const;
#endif

    auto LogicalVolumeNum() const { return std::ssize(fLogicalVolumes); }
    auto LogicalVolume(gsl::index volumeIndex = 0) const { return fLogicalVolumes.at(volumeIndex).get(); }

    auto PhysicalVolumeNum() const { return std::ssize(fPhysicalVolumes); }
    auto PhysicalVolume(gsl::index volumeIndex = 0) const { return fPhysicalVolumes.at(volumeIndex).get(); }

protected:
    // Make a G4Solid and keep it (just for deleting when Entity deconstructs).
    template<std::derived_from<G4VSolid> ASolid>
    gsl::not_null<ASolid*> Make(auto&&... args);
    // Make a G4LogicalVolume and keep it for futher access. Will be deleted when Entity deconstructed.
    template<std::derived_from<G4LogicalVolume> ALogical>
    gsl::not_null<ALogical*> Make(auto&&... args);
    // Make a G4PhysicalVolume and keep it for futher access. Will be deleted when Entity deconstructed.
    template<std::derived_from<G4VPhysicalVolume> APhysical>
    gsl::not_null<APhysical*> Make(auto&&... args);

    // shared_ptr points to the mother Entity.
    auto Mother() const { return std::static_pointer_cast<const IEntity>(fMother); }

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
