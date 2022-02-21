#include "G4GDMLParser.hh"

#include "Geometry/Interface/Entity.hxx"

using namespace MACE::Geometry::Interface;

Entity::Entity() :
    std::enable_shared_from_this<Entity>(),
    fMother(nullptr),
    fDaughters(0),
    fSolidStore(0),
    fLogicalVolumeStore(0),
    fPhysicalVolumes(0) {}

void Entity::AddDaughter(const std::shared_ptr<Entity>& daughter) {
    if (daughter->fMother != nullptr) {
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

void Entity::WriteSelfAndDesendentsToGDML(std::string_view fileName, size_t volumeIndex) const {
    G4GDMLParser gdml;
    gdml.SetAddPointerToName(false);
    gdml.SetOutputFileOverwrite(true);
    gdml.Write(fileName.data(), this->GetPhysicalVolume(volumeIndex));
}
