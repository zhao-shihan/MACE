namespace MACE::inline Utility::internal {

template<typename ATime>
CPUTimer<ATime>::CPUTimer() noexcept :
    fT0(std::clock()) {}

} // namespace MACE::inline Utility::internal
