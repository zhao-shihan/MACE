#pragma once

#include "MACE/Utility/NonMoveableBase.hxx"

#include "G4ChordFinder.hh"
#include "G4EquationOfMotion.hh"
#include "G4Exception.hh"
#include "G4Field.hh"
#include "G4FieldManager.hh"
#include "G4LogicalVolume.hh"
#include "G4Region.hh"
#include "G4VIntegrationDriver.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VSensitiveDetector.hh"
#include "G4VSolid.hh"

#include "gsl/gsl"

#include <filesystem>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <typeindex>
#include <typeinfo>
#include <vector>

namespace MACE::Detector {

class GeometryBase : public NonMoveableBase {
public:
    virtual ~GeometryBase() = default;

    auto IsTop() const { return not fMother.has_value(); }
    const auto& Mother() const { return fMother.value().get(); }

    /// @brief Determines whether we will construct this entity.
    /// Entities could override this function to control whether this will be constructed.
    /// A typical usage is to get the information of whether to enable this from description in the override function.
    virtual bool Enabled() const { return true; }

    template<std::derived_from<GeometryBase> AEntity>
    AEntity& NewDaughter(G4bool checkOverlaps);
    template<std::derived_from<GeometryBase> AEntity>
    std::optional<std::reference_wrapper<AEntity>> FindDaughter() const;
    template<std::derived_from<GeometryBase> AEntity>
    auto RemoveDaughter() { return fDaughters.erase(typeid(AEntity)) > 0; }

    void RegisterMaterial(gsl::index iLogicalVolume, gsl::not_null<G4Material*> material) const;
    void RegisterMaterial(gsl::not_null<G4Material*> material) const;

    void RegisterRegion(gsl::index iLogicalVolume, gsl::not_null<G4Region*> region) const;
    void RegisterRegion(gsl::not_null<G4Region*> region) const;

    void RegisterSD(gsl::index iLogicalVolume, gsl::not_null<G4VSensitiveDetector*> sd) const;
    void RegisterSD(gsl::not_null<G4VSensitiveDetector*> sd) const;

    template<std::derived_from<G4Field> AField, std::derived_from<G4EquationOfMotion> AEquation, class AStepper, std::derived_from<G4VIntegrationDriver> ADriver>
    void RegisterField(gsl::index iLogicalVolume, gsl::not_null<AField*> field, G4double hMin, G4int nVarStepper, G4int nVarDriver, G4bool propagateToDescendants) const;
    template<std::derived_from<G4Field> AField, std::derived_from<G4EquationOfMotion> AEquation, class AStepper, std::derived_from<G4VIntegrationDriver> ADriver>
    void RegisterField(gsl::not_null<AField*> field, G4double hMin, G4int nVarStepper, G4int nVarDriver, G4bool propagateToDescendants) const;

    void Export(std::filesystem::path gdmlFile, gsl::index iPhysicalVolume = 0) const;

    const auto& LogicalVolumes() const { return fLogicalVolumes; }
    const auto& LogicalVolume(gsl::index i = 0) const { return fLogicalVolumes.at(i); }
    const auto& PhysicalVolumes() const { return fPhysicalVolumes; }
    const auto& PhysicalVolume(gsl::index i = 0) const { return fPhysicalVolumes.at(i); }

protected:
    // Make a G4Solid and keep it (for deleting when Entity deconstructs).
    template<std::derived_from<G4VSolid> ASolid>
    ASolid* Make(auto&&... args);
    // Make a G4LogicalVolume and keep it for futher access. Will be deleted when Entity deconstructed.
    template<std::derived_from<G4LogicalVolume> ALogical>
    ALogical* Make(auto&&... args);
    // Make a G4PhysicalVolume and keep it for futher access. Will be deleted when Entity deconstructed.
    template<std::derived_from<G4VPhysicalVolume> APhysical>
    APhysical* Make(auto&&... args);

private:
    virtual void Construct(G4bool checkOverlaps) = 0;

private:
    std::optional<std::reference_wrapper<const GeometryBase>> fMother;

    std::vector<std::unique_ptr<G4VSolid>> fSolidStore;
    std::vector<std::unique_ptr<G4LogicalVolume>> fLogicalVolumes;
    std::vector<std::unique_ptr<G4VPhysicalVolume>> fPhysicalVolumes;

    std::map<std::type_index, std::unique_ptr<GeometryBase>> fDaughters;
};

} // namespace MACE::Detector

#include "MACE/Detector/GeometryBase.inl"
