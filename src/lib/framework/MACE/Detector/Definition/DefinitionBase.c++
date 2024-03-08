#include "MACE/Detector/Definition/DefinitionBase.h++"
#include "MACE/Env/MPIEnv.h++"
#include "MACE/Extension/MPIX/ParallelizePath.h++"

#include "G4GDMLParser.hh"
#include "G4SDManager.hh"

#include "fmt/format.h"

namespace MACE::Detector::Definition {

namespace internal {
namespace {

auto RegisterMaterial(G4LogicalVolume* logic, gsl::not_null<G4Material*> material) -> void {
    logic->SetMaterial(material);
}

auto RegisterRegion(G4LogicalVolume* logic, gsl::not_null<G4Region*> region) -> void {
    if (logic->GetRegion() != region) {
        logic->SetRegion(region);
        region->AddRootLogicalVolume(logic);
    }
}

auto RegisterSD(G4LogicalVolume* logic, gsl::not_null<G4VSensitiveDetector*> sd) -> void {
    if (logic->GetSensitiveDetector() == nullptr) {
        // Register to logicalVolume
        logic->SetSensitiveDetector(sd);
        // Register to G4SDManager
        const auto sdManager{G4SDManager::GetSDMpointer()};
        if (sdManager->FindSensitiveDetector(sd->GetFullPathName(), false) == nullptr) {
            sdManager->AddNewDetector(sd);
        }
    } else if (logic->GetSensitiveDetector() != sd) {
        G4Exception("MACE::Detector::Definition::DefinitionBase::RegisterSD", "-1", JustWarning,
                    fmt::format("Attempting to register SD multiple times for \"{}\" is currently not supported "
                                "(G4MultiSensitiveDetector not supported currently), skipping.",
                                logic->GetName())
                        .c_str());
    } else {
        G4Exception("MACE::Detector::Definition::DefinitionBase::RegisterSD", "-1", JustWarning,
                    fmt::format("Attempting to register the same SD multiple times for \"{}\", skipping.",
                                logic->GetName())
                        .c_str());
    }
}

auto Export(std::filesystem::path gdmlFile, G4LogicalVolume* logic) {
    if (Env::MPIEnv::Available()) { MPIX::ParallelizePathInPlace(gdmlFile); }
    G4GDMLParser gdml;
    gdml.SetAddPointerToName(true);
    gdml.SetOutputFileOverwrite(true);
    gdml.Write(gdmlFile.generic_string(), logic);
}

} // namespace
} // namespace internal

auto DefinitionBase::RegisterMaterial(gsl::not_null<G4Material*> material) const -> void {
    if (not Ready()) { return; }
    const auto& lvs{LogicalVolumes()};
    assert(lvs.size() > 0);
    for (auto&& lv : lvs) {
        internal::RegisterMaterial(lv, material);
    }
}

auto DefinitionBase::RegisterMaterial(std::string_view logicalVolumeName, gsl::not_null<G4Material*> material) const -> void {
    if (not Ready()) { return; }
    const auto& lvs{LogicalVolumes(logicalVolumeName)};
    assert(lvs.size() > 0);
    for (auto&& lv : lvs) {
        internal::RegisterMaterial(lv, material);
    }
}

auto DefinitionBase::RegisterMaterial(gsl::index iLogicalVolume, gsl::not_null<G4Material*> material) const -> void {
    if (not Ready()) { return; }
    internal::RegisterMaterial(LogicalVolume(iLogicalVolume), material);
}

auto DefinitionBase::RegisterMaterial(std::string_view logicalVolumeName, gsl::index iLogicalVolume, gsl::not_null<G4Material*> material) const -> void {
    if (not Ready()) { return; }
    internal::RegisterMaterial(LogicalVolume(logicalVolumeName, iLogicalVolume), material);
}

auto DefinitionBase::RegisterRegion(gsl::not_null<G4Region*> region) const -> void {
    if (not Ready()) { return; }
    const auto& lvs{LogicalVolumes()};
    assert(lvs.size() > 0);
    for (auto&& lv : lvs) {
        internal::RegisterRegion(lv, region);
    }
}

auto DefinitionBase::RegisterRegion(std::string_view logicalVolumeName, gsl::not_null<G4Region*> region) const -> void {
    if (not Ready()) { return; }
    const auto& lvs{LogicalVolumes(logicalVolumeName)};
    assert(lvs.size() > 0);
    for (auto&& lv : lvs) {
        internal::RegisterRegion(lv, region);
    }
}

auto DefinitionBase::RegisterRegion(gsl::index iLogicalVolume, gsl::not_null<G4Region*> region) const -> void {
    if (not Ready()) { return; }
    internal::RegisterRegion(LogicalVolume(iLogicalVolume), region);
}

auto DefinitionBase::RegisterRegion(std::string_view logicalVolumeName, gsl::index iLogicalVolume, gsl::not_null<G4Region*> region) const -> void {
    if (not Ready()) { return; }
    internal::RegisterRegion(LogicalVolume(logicalVolumeName, iLogicalVolume), region);
}

auto DefinitionBase::RegisterSD(gsl::not_null<G4VSensitiveDetector*> sd) const -> void {
    if (not Ready()) { return; }
    const auto& lvs{LogicalVolumes()};
    assert(lvs.size() > 0);
    for (auto&& lv : lvs) {
        internal::RegisterSD(lv, sd);
    }
}

auto DefinitionBase::RegisterSD(std::string_view logicalVolumeName, gsl::not_null<G4VSensitiveDetector*> sd) const -> void {
    if (not Ready()) { return; }
    const auto& lvs{LogicalVolumes(logicalVolumeName)};
    assert(lvs.size() > 0);
    for (auto&& lv : lvs) {
        internal::RegisterSD(lv, sd);
    }
}

auto DefinitionBase::RegisterSD(gsl::index iLogicalVolume, gsl::not_null<G4VSensitiveDetector*> sd) const -> void {
    if (not Ready()) { return; }
    internal::RegisterSD(LogicalVolume(iLogicalVolume), sd);
}

auto DefinitionBase::RegisterSD(std::string_view logicalVolumeName, gsl::index iLogicalVolume, gsl::not_null<G4VSensitiveDetector*> sd) const -> void {
    if (not Ready()) { return; }
    internal::RegisterSD(LogicalVolume(logicalVolumeName, iLogicalVolume), sd);
}

auto DefinitionBase::Export(std::filesystem::path gdmlFile, gsl::index iPhysicalVolume) const -> void {
    if (not Ready()) { return; }
    internal::Export(std::move(gdmlFile), LogicalVolume(iPhysicalVolume));
}

auto DefinitionBase::Export(std::filesystem::path gdmlFile, std::string_view physicalVolumeName, gsl::index iPhysicalVolume) const -> void {
    if (not Ready()) { return; }
    internal::Export(std::move(gdmlFile), LogicalVolume(physicalVolumeName, iPhysicalVolume));
}

auto DefinitionBase::LogicalVolumes() const -> const std::vector<G4LogicalVolume*>& {
    if (fFirstLogicalVolumes == nullptr) { throw std::logic_error{"no logical volume"}; }
    assert(not fLogicalVolumes.empty());
    return *fFirstLogicalVolumes;
}

auto DefinitionBase::PhysicalVolumes() const -> const std::vector<G4VPhysicalVolume*>& {
    if (fFirstPhysicalVolumes == nullptr) { throw std::logic_error{"no physical volume"}; }
    assert(not fPhysicalVolumes.empty());
    return *fFirstPhysicalVolumes;
}

} // namespace MACE::Detector::Definition
