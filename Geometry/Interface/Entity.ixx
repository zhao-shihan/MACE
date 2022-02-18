template<class Volume_t>
MACE::Geometry::Interface::Entity<Volume_t>::Entity() :
    std::enable_shared_from_this<MACE::Geometry::Interface::Entity<Volume_t>>(),
    fVolumes(0),
    fMother(),
    fDaughters(0) {}

template<class Volume_t>
MACE::Geometry::Interface::Entity<Volume_t>::~Entity() noexcept {
    for (auto&& volume : fVolumes) { delete volume; }
}

template<class Volume_t>
void MACE::Geometry::Interface::Entity<Volume_t>::AddDaughter(const std::shared_ptr<Entity>& daughter) {
    this->fDaughters.emplace_back(daughter);
    try {
        daughter->fMother = this->shared_from_this();
    } catch (std::bad_weak_ptr& exception) {
        std::cout << "Exception from (...)::Entity<Volume_t>::AddDaughter(...): " << exception.what() << '\n'
            << "Notice: Objects of MACE::Geometry::Interface::Entity<Volume_t> derivations should be managed by std::shared_ptr<...>!" << std::endl;
    }
}

template<class Volume_t>
void MACE::Geometry::Interface::Entity<Volume_t>::ConstructSelfAndDescendants(bool checkOverlaps) {
    this->ConstructSelf(checkOverlaps);
    for (auto&& daughter : fDaughters) {
        daughter->ConstructSelfAndDescendants(checkOverlaps);
    }
}
