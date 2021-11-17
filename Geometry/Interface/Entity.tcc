template<class VolumeType>
MACE::Geometry::Interface::Entity<VolumeType>::Entity() :
    fMother(nullptr),
    fVolumes(0),
    fDaughters(0) {}

template<class VolumeType>
MACE::Geometry::Interface::Entity<VolumeType>::~Entity() {
    for (auto&& daughter : fDaughters) { delete daughter; }
    for (auto&& volume : fVolumes) { delete volume; }
}

template<class VolumeType>
void MACE::Geometry::Interface::Entity<VolumeType>::AddDaughter(MACE::Geometry::Interface::Entity<VolumeType>* daughter) {
    this->fDaughters.emplace_back(daughter);
    daughter->fMother = this;
}

template<class VolumeType>
void MACE::Geometry::Interface::Entity<VolumeType>::CreateSelfAndDescendants() {
    this->CreateSelf();
    for (auto&& daughter : fDaughters) {
        daughter->CreateSelfAndDescendants();
    }
}
