namespace MACE::inline Utility::internal {

template<typename ATime>
CPUTimeStopwatch<ATime>::CPUTimeStopwatch() noexcept :
    fT0(std::clock()) {}

} // namespace MACE::inline Utility::internal
