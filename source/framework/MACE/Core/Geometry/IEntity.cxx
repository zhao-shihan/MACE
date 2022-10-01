#include "MACE/Core/Geometry/IEntity.hxx"
#include "MACE/Env/MPIEnv.hxx"
#include "MACE/Utility/MPIUtil/MakeMPIFilePath.hxx"

#include "G4SDManager.hh"

#if MACE_USE_G4GDML
#    include "G4GDMLParser.hh"
#endif

namespace MACE::Core::Geometry {

IEntity::IEntity() :
    std::enable_shared_from_this<IEntity>(),
    fMother(nullptr),
    fDaughters(0),
    fSolidStore(0),
    fLogicalVolumes(0),
    fPhysicalVolumes(0) {}

void IEntity::AddDaughter(const std::shared_ptr<IEntity>& daughter) {
    if (daughter->fMother != nullptr) {
        std::cerr << "Error: Entity " << daughter << " already registered to " << daughter->fMother
                  << " as a daughter, but now trying again to register to " << this
                  << " as a daughter. Please check the geometry hierarchy.\n";
        return;
    }
    try {
        daughter->fMother = shared_from_this();
    } catch (const std::bad_weak_ptr& exception) {
        std::cerr << "Exception from (...)::IEntity::AddDaughter(...): " << exception.what() << '\n'
                  << "  Notice: Objects of IEntity derivations should be managed by std::shared_ptr\n";
        throw exception;
    }
    fDaughters.emplace_back(daughter);
}

void IEntity::ConstructSelfAndDescendants(G4bool checkOverlaps) {
    if (this->Enabled()) { this->ConstructSelf(checkOverlaps); }
    for (auto&& daughter : std::as_const(fDaughters)) {
        daughter.lock()->ConstructSelfAndDescendants(checkOverlaps);
    }
}

void IEntity::RegisterMaterial(std::size_t volumeIndex, G4Material* region) const {
    LogicalVolume(volumeIndex)->SetMaterial(region);
}

void IEntity::RegisterMaterial(G4Material* region) const {
    for (std::size_t i = 0; i < LogicalVolumeNum(); ++i) {
        RegisterMaterial(i, region);
    }
}

void IEntity::RegisterRegion(std::size_t volumeIndex, G4Region* region) const {
    auto logicalVolume = LogicalVolume(volumeIndex);
    if (logicalVolume->GetRegion() != region) {
        logicalVolume->SetRegion(region);
        region->AddRootLogicalVolume(logicalVolume);
    }
}

void IEntity::RegisterRegion(G4Region* region) const {
    for (std::size_t i = 0; i < LogicalVolumeNum(); ++i) {
        RegisterRegion(i, region);
    }
}

void IEntity::RegisterSD(std::size_t volumeIndex, G4VSensitiveDetector* sd) const {
    auto logicalVolume = LogicalVolume(volumeIndex);
    if (logicalVolume->GetSensitiveDetector() == nullptr) {
        // Register to logicalVolume
        logicalVolume->SetSensitiveDetector(sd);
        // Register to G4SDManager
        auto sdManager = G4SDManager::GetSDMpointer();
        if (sdManager->FindSensitiveDetector(sd->GetFullPathName(), false) == nullptr) {
            sdManager->AddNewDetector(sd);
        }
    } else if (logicalVolume->GetSensitiveDetector() != sd) {
        G4ExceptionDescription msg;
        msg << "Attempting to register SD multiple times for \"" << logicalVolume->GetName() << "\" is currently not supported "
            << "(G4MultiSensitiveDetector not supported currently), skipping.";
        G4Exception("MACE::Core::Geometry::IEntity::RegisterSD", "-1", JustWarning, msg);
    } else {
        G4ExceptionDescription msg;
        msg << "Attempting to register the same SD multiple times for \"" << logicalVolume->GetName() << "\", skipping.";
        G4Exception("MACE::Core::Geometry::IEntity::RegisterSD", "-1", JustWarning, msg);
    }
}

void IEntity::RegisterSD(G4VSensitiveDetector* sd) const {
    for (std::size_t i = 0; i < LogicalVolumeNum(); ++i) {
        RegisterSD(i, sd);
    }
}

#if MACE_USE_G4GDML
void IEntity::Export(std::filesystem::path gdmlFile, std::size_t volumeIndex) const {
    if (Env::MPIEnv::Available()) {
        Utility::MPIUtil::MakeMPIFilePathInPlace(gdmlFile);
    }
    G4GDMLParser gdml;
    gdml.SetAddPointerToName(false);
    gdml.SetOutputFileOverwrite(true);
    gdml.Write(gdmlFile.generic_string(), this->PhysicalVolume(volumeIndex));
}
#endif

} // namespace MACE::Core::Geometry
