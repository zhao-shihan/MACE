namespace MACE::Geant4X {

template<class ADerived>
UseG4Allocator<ADerived>::UseG4Allocator() {
    static_assert(std::derived_from<ADerived, UseG4Allocator<ADerived>>);
    static_assert(std::is_final_v<ADerived>);
}

template<class ADerived>
[[nodiscard]] void* UseG4Allocator<ADerived>::operator new(std::size_t) {
    return SingletonG4Allocator<ADerived>::Instance().MallocSingle();
}

template<class ADerived>
void UseG4Allocator<ADerived>::operator delete(void* ptr) {
    SingletonG4Allocator<ADerived>::Instance().FreeSingle(static_cast<ADerived*>(ptr));
}

} // namespace MACE::Geant4X
