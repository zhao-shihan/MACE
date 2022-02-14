template<class Volume_t>
MACE::Geometry::Interface::Entity<Volume_t>::Entity() :
    fMother(nullptr),
    fVolumes(0),
    fDaughters(0) {}

template<class Volume_t>
MACE::Geometry::Interface::Entity<Volume_t>::~Entity() noexcept {
    for (auto&& daughter : fDaughters) { delete daughter; }
    for (auto&& volume : fVolumes) { delete volume; }
}

template<class Volume_t>
void MACE::Geometry::Interface::Entity<Volume_t>::AddDaughter(MACE::Geometry::Interface::Entity<Volume_t>* daughter) {
    this->fDaughters.emplace_back(daughter);
    daughter->fMother = this;
}

template<class Volume_t>
void MACE::Geometry::Interface::Entity<Volume_t>::ConstructSelfAndDescendants() {
    this->ConstructSelf();
    for (auto&& daughter : fDaughters) {
        daughter->ConstructSelfAndDescendants();
    }
}
