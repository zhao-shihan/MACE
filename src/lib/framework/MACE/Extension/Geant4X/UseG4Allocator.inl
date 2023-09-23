namespace MACE::inline Extension::Geant4X {

template<class ADerived>
[[nodiscard]] MACE_ALWAYS_INLINE auto UseG4Allocator<ADerived>::operator new(std::size_t) -> void* {
    static_assert(std::derived_from<ADerived, UseG4Allocator<ADerived>>);
    static_assert(std::is_final_v<ADerived>);
    return SingletonG4Allocator<ADerived>::Instance().MallocSingle();
}

template<class ADerived>
MACE_ALWAYS_INLINE auto UseG4Allocator<ADerived>::operator delete(void* ptr) -> void {
    SingletonG4Allocator<ADerived>::Instance().FreeSingle(static_cast<ADerived*>(ptr));
}

} // namespace MACE::inline Extension::Geant4X
