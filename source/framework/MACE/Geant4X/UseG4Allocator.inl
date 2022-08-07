namespace MACE::Geant4X {

template<class ADerived>
UseG4Allocator<ADerived>::UseG4Allocator() {
    static_assert(std::derived_from<ADerived, UseG4Allocator<ADerived>>);
    static_assert(std::is_final_v<ADerived>);
}

} // namespace MACE::SimulationG4
