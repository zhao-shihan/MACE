#include "MACE/Detector/Definition/DefinitionBase.h++"
#include "MACE/Env/MPIEnv.h++"
#include "MACE/Extension/MPIX/ParallelizePath.h++"

#include "G4SDManager.hh"

#include "fmt/format.h"

#if MACE_USE_G4GDML
#    include "G4GDMLParser.hh"
#endif

namespace MACE::Detector::Definition {

namespace internal {
namespace {

auto RegisterMaterial(const std::unique_ptr<G4LogicalVolume>& logic, gsl::not_null<G4Material*> material) -> void {
    logic->SetMaterial(material);
}

auto RegisterRegion(const std::unique_ptr<G4LogicalVolume>& logic, gsl::not_null<G4Region*> region) -> void {
    if (logic->GetRegion() != region) {
        logic->SetRegion(region);
        region->AddRootLogicalVolume(logic.get());
    }
}

auto RegisterSD(const std::unique_ptr<G4LogicalVolume>& logic, gsl::not_null<G4VSensitiveDetector*> sd) -> void {
    if (logic->GetSensitiveDetector() == nullptr) {
        // Register to logicalVolume
        logic->SetSensitiveDetector(sd);
        // Register to G4SDManager
        const auto sdManager{G4SDManager::GetSDMpointer()};
        if (sdManager->FindSensitiveDetector(sd->GetFullPathName(), false) == nullptr) {
            sdManager->AddNewDetector(sd);
        }
    } else if (logic->GetSensitiveDetector() != sd) {
        G4Exception("MACE::Detector::Definition::GeometryBase::RegisterSD", "-1", JustWarning,
                    fmt::format("Attempting to register SD multiple times for \"{}\" is currently not supported "
                                "(G4MultiSensitiveDetector not supported currently), skipping.",
                                logic->GetName())
                        .c_str());
    } else {
        G4Exception("MACE::Detector::Definition::GeometryBase::RegisterSD", "-1", JustWarning,
                    fmt::format("Attempting to register the same SD multiple times for \"{}\", skipping.",
                                logic->GetName())
                        .c_str());
    }
}

auto Export(std::filesystem::path gdmlFile, const std::unique_ptr<G4VPhysicalVolume>& physics) {
#if MACE_USE_G4GDML
    if (Env::MPIEnv::Available()) { MPIX::ParallelizePathInPlace(gdmlFile); }
    G4GDMLParser gdml;
    gdml.SetAddPointerToName(true);
    gdml.SetOutputFileOverwrite(true);
    gdml.Write(gdmlFile.generic_string(), physics.get());
#else
    G4Exception("MACE::Detector::Definition::GeometryBase::Export", "-1", JustWarning,
                "This binary does not support GDML export (MACE_USE_G4GDML=OFF). "
                "Try with a binary configured with MACE_USE_G4GDML=ON. "
                "Nothing was done for the time being.");
#endif
}

} // namespace
} // namespace internal

auto GeometryBase::RegisterMaterial(gsl::not_null<G4Material*> material) const -> void {
    if (not Ready()) { return; }
    const auto& lvs{LogicalVolumes()};
    assert(lvs.size() > 0);
    for (auto&& lv : lvs) {
        internal::RegisterMaterial(lv, material);
    }
}

auto GeometryBase::RegisterMaterial(std::string_view logicalVolumeName, gsl::not_null<G4Material*> material) const -> void {
    if (not Ready()) { return; }
    const auto& lvs{LogicalVolumes(logicalVolumeName)};
    assert(lvs.size() > 0);
    for (auto&& lv : lvs) {
        internal::RegisterMaterial(lv, material);
    }
}

auto GeometryBase::RegisterMaterial(gsl::index iLogicalVolume, gsl::not_null<G4Material*> material) const -> void {
    if (not Ready()) { return; }
    internal::RegisterMaterial(LogicalVolume(iLogicalVolume), material);
}

auto GeometryBase::RegisterMaterial(std::string_view logicalVolumeName, gsl::index iLogicalVolume, gsl::not_null<G4Material*> material) const -> void {
    if (not Ready()) { return; }
    internal::RegisterMaterial(LogicalVolume(logicalVolumeName, iLogicalVolume), material);
}

auto GeometryBase::RegisterRegion(gsl::not_null<G4Region*> region) const -> void {
    if (not Ready()) { return; }
    const auto& lvs{LogicalVolumes()};
    assert(lvs.size() > 0);
    for (auto&& lv : lvs) {
        internal::RegisterRegion(lv, region);
    }
}

auto GeometryBase::RegisterRegion(std::string_view logicalVolumeName, gsl::not_null<G4Region*> region) const -> void {
    if (not Ready()) { return; }
    const auto& lvs{LogicalVolumes(logicalVolumeName)};
    assert(lvs.size() > 0);
    for (auto&& lv : lvs) {
        internal::RegisterRegion(lv, region);
    }
}

auto GeometryBase::RegisterRegion(gsl::index iLogicalVolume, gsl::not_null<G4Region*> region) const -> void {
    if (not Ready()) { return; }
    internal::RegisterRegion(LogicalVolume(iLogicalVolume), region);
}

auto GeometryBase::RegisterRegion(std::string_view logicalVolumeName, gsl::index iLogicalVolume, gsl::not_null<G4Region*> region) const -> void {
    if (not Ready()) { return; }
    internal::RegisterRegion(LogicalVolume(logicalVolumeName, iLogicalVolume), region);
}

auto GeometryBase::RegisterSD(gsl::not_null<G4VSensitiveDetector*> sd) const -> void {
    if (not Ready()) { return; }
    const auto& lvs{LogicalVolumes()};
    assert(lvs.size() > 0);
    for (auto&& lv : lvs) {
        internal::RegisterSD(lv, sd);
    }
}

auto GeometryBase::RegisterSD(std::string_view logicalVolumeName, gsl::not_null<G4VSensitiveDetector*> sd) const -> void {
    if (not Ready()) { return; }
    const auto& lvs{LogicalVolumes(logicalVolumeName)};
    assert(lvs.size() > 0);
    for (auto&& lv : lvs) {
        internal::RegisterSD(lv, sd);
    }
}

auto GeometryBase::RegisterSD(gsl::index iLogicalVolume, gsl::not_null<G4VSensitiveDetector*> sd) const -> void {
    if (not Ready()) { return; }
    internal::RegisterSD(LogicalVolume(iLogicalVolume), sd);
}

auto GeometryBase::RegisterSD(std::string_view logicalVolumeName, gsl::index iLogicalVolume, gsl::not_null<G4VSensitiveDetector*> sd) const -> void {
    if (not Ready()) { return; }
    internal::RegisterSD(LogicalVolume(logicalVolumeName, iLogicalVolume), sd);
}

auto GeometryBase::Export(std::filesystem::path gdmlFile, gsl::index iPhysicalVolume) const -> void {
    if (not Ready()) { return; }
    internal::Export(std::move(gdmlFile), PhysicalVolume(iPhysicalVolume));
}

auto GeometryBase::Export(std::filesystem::path gdmlFile, std::string_view physicalVolumeName, gsl::index iPhysicalVolume) const -> void {
    if (not Ready()) { return; }
    internal::Export(std::move(gdmlFile), PhysicalVolume(physicalVolumeName, iPhysicalVolume));
}

auto GeometryBase::LogicalVolumes() const -> const std::vector<std::unique_ptr<G4LogicalVolume>>& {
    if (fLogicalVolumes.size() == 0) { throw std::out_of_range{"no logical volume"}; }
    return fLogicalVolumes.begin()->second;
}

auto GeometryBase::PhysicalVolumes() const -> const std::vector<std::unique_ptr<G4VPhysicalVolume>>& {
    if (fPhysicalVolumes.size() == 0) { throw std::out_of_range{"no physical volume"}; }
    return fPhysicalVolumes.begin()->second;
}

} // namespace MACE::Detector::Definition
