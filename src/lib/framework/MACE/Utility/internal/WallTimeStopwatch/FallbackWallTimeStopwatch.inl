namespace MACE::inline Utility::internal {

template<typename ATime>
WallTimeStopwatch<ATime>::WallTimeStopwatch() noexcept :
    fT0(sc::now()) {}

} // namespace MACE::inline Utility::internal
