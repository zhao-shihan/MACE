#include "G4SDManager.hh"
#include "G4GDMLParser.hh"

#include "Geometry/Interface/Entity.hxx"

using namespace MACE::Geometry::Interface;

Entity::Entity() :
    std::enable_shared_from_this<Entity>(),
    fMother(nullptr),
    fDaughters(0),
    fSolidStore(0),
    fLogicalVolumes(0),
    fPhysicalVolumes(0) {}

void Entity::AddDaughter(const std::shared_ptr<Entity>& daughter) {
    if (daughter->fMother) {
        std::cerr << "Error: Entity " << daughter << " already registered to " << daughter->fMother << " as a daughter,\n"
            "\tbut now trying again to register to " << this << " as a daughter. Please check the geometry hierarchy." << std::endl;
        return;
    }
    try {
        daughter->fMother = shared_from_this();
    } catch (const std::bad_weak_ptr& exception) {
        std::cerr << "Exception from (...)::Entity<Volume_t>::AddDaughter(...): " << exception.what() << '\n'
            << "Notice: Objects of Entity<Volume_t> derivations should be managed by std::shared_ptr<...>!" << std::endl;
        throw exception;
    }
    fDaughters.emplace_back(daughter);
}

void Entity::ConstructSelfAndDescendants(G4bool checkOverlaps) {
    this->ConstructSelf(checkOverlaps);
    for (auto&& daughter : fDaughters) {
        daughter.lock()->ConstructSelfAndDescendants(checkOverlaps);
    }
}

void Entity::RegisterRegion(size_t volumeIndex, G4Region* region) const {
    auto logicalVolume = GetLogicalVolume(volumeIndex);
    if (logicalVolume->GetRegion() != region) {
        logicalVolume->SetRegion(region);
        region->AddRootLogicalVolume(logicalVolume);
    }
}

void Entity::RegisterRegion(G4Region* region) const {
    for (size_t i = 0; i < GetLogicalVolumeNum(); ++i) {
        RegisterRegion(i, region);
    }
}

void Entity::RegisterSensitiveDetector(size_t volumeIndex, G4VSensitiveDetector* sd) const {
    auto logicalVolume = GetLogicalVolume(volumeIndex);
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
            "(G4MultiSensitiveDetector not supported currently), skipping.";
        G4Exception("MACE::Geometry::Interface::Entity::RegisterSensitiveDetector", "-1", JustWarning, msg);
    } else {
        G4ExceptionDescription msg;
        msg << "Attempting to register the same SD multiple times for \"" << logicalVolume->GetName() << "\", skipping.";
        G4Exception("MACE::Geometry::Interface::Entity::RegisterSensitiveDetector", "-1", JustWarning, msg);
    }
}

void Entity::RegisterSensitiveDetector(G4VSensitiveDetector* sd) const {
    for (size_t i = 0; i < GetLogicalVolumeNum(); ++i) {
        RegisterSensitiveDetector(i, sd);
    }
}

void Entity::WriteSelfAndDesendentsToGDML(std::string_view fileName, size_t volumeIndex) const {
    G4GDMLParser gdml;
    gdml.SetAddPointerToName(false);
    gdml.SetOutputFileOverwrite(true);
    gdml.Write(fileName.data(), this->GetPhysicalVolume(volumeIndex));
}
