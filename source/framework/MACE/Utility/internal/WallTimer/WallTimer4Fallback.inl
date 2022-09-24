namespace MACE::Utility::internal {

template<typename ATime>
WallTimer<ATime>::WallTimer() noexcept :
    fT0(sc::now()) {}

} // namespace MACE::Utility::internal
