#pragma once

#include "MACE/Utility/NonMoveableBase.h++"

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
#include <memory>
#include <optional>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <vector>

namespace MACE::Detector::Geometry {

class GeometryBase : public NonMoveableBase {
public:
    virtual ~GeometryBase() = default;

    auto Topmost() const -> bool { return not fMother.has_value(); }
    auto Mother() const -> const auto& { return fMother.value().get(); }

    /// @brief Determines whether we will construct this geometry.
    /// Entities could override this function to control whether this will be constructed.
    /// A typical usage is to get the information of whether to enable this from description in the override function.
    virtual bool Enabled() const { return true; }

    template<std::derived_from<GeometryBase> AGeometry>
    auto NewDaughter(G4bool checkOverlaps) -> AGeometry&;
    template<std::derived_from<GeometryBase> AGeometry>
    auto FindDaughter() const -> std::optional<std::reference_wrapper<AGeometry>>;
    template<std::derived_from<GeometryBase> AGeometry>
    auto RemoveDaughter() -> bool { return fDaughters.erase(typeid(AGeometry)) > 0; }
    template<std::derived_from<GeometryBase> AGeometry>
    auto FindSibling() const -> auto { return Mother().FindDaughter<AGeometry>(); }

    auto RegisterMaterial(gsl::index iLogicalVolume, gsl::not_null<G4Material*> material) const -> void;
    auto RegisterMaterial(gsl::not_null<G4Material*> material) const -> void;

    auto RegisterRegion(gsl::index iLogicalVolume, gsl::not_null<G4Region*> region) const -> void;
    auto RegisterRegion(gsl::not_null<G4Region*> region) const -> void;

    auto RegisterSD(gsl::index iLogicalVolume, gsl::not_null<G4VSensitiveDetector*> sd) const -> void;
    auto RegisterSD(std::string_view logicalVolumeName, gsl::not_null<G4VSensitiveDetector*> sd) const -> void;
    auto RegisterSD(gsl::not_null<G4VSensitiveDetector*> sd) const -> void;

    template<std::derived_from<G4Field> AField, std::derived_from<G4EquationOfMotion> AEquation, typename AStepper, std::derived_from<G4VIntegrationDriver> ADriver>
    auto RegisterField(gsl::index iLogicalVolume, gsl::not_null<AField*> field, G4double hMin, G4int nVarStepper, G4int nVarDriver, G4bool forceToAllDaughters) const -> void;
    template<std::derived_from<G4Field> AField, std::derived_from<G4EquationOfMotion> AEquation, typename AStepper, std::derived_from<G4VIntegrationDriver> ADriver>
    auto RegisterField(gsl::not_null<AField*> field, G4double hMin, G4int nVarStepper, G4int nVarDriver, G4bool forceToAllDaughters) const -> void;

    auto Export(std::filesystem::path gdmlFile, gsl::index iPhysicalVolume = 0) const -> void;

    auto LogicalVolumes() const -> const auto& { return fLogicalVolumes; }
    auto LogicalVolume(gsl::index i = 0) const -> const auto& { return fLogicalVolumes.at(i); }
    auto PhysicalVolumes() const -> const auto& { return fPhysicalVolumes; }
    auto PhysicalVolume(gsl::index i = 0) const -> const auto& { return fPhysicalVolumes.at(i); }

protected:
    // Make a G4Solid and keep it (for deleting when geometry deconstructs).
    template<std::derived_from<G4VSolid> ASolid>
    auto Make(auto&&... args) -> ASolid*;
    // Make a G4LogicalVolume and keep it for futher access. Will be deleted when geometry deconstructed.
    template<std::derived_from<G4LogicalVolume> ALogical>
    auto Make(auto&&... args) -> ALogical*;
    // Make a G4PhysicalVolume and keep it for futher access. Will be deleted when geometry deconstructed.
    template<std::derived_from<G4VPhysicalVolume> APhysical>
    auto Make(auto&&... args) -> APhysical*;

private:
    virtual auto Construct(G4bool checkOverlaps) -> void = 0;

private:
    std::optional<std::reference_wrapper<const GeometryBase>> fMother;

    std::vector<std::unique_ptr<G4VSolid>> fSolidStore;
    std::vector<std::unique_ptr<G4LogicalVolume>> fLogicalVolumes;
    std::vector<std::unique_ptr<G4VPhysicalVolume>> fPhysicalVolumes;

    std::unordered_map<std::type_index, std::unique_ptr<GeometryBase>> fDaughters;
};

} // namespace MACE::Detector::Geometry

#include "MACE/Detector/Geometry/GeometryBase.inl"
