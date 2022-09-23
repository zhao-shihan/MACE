namespace MACE::Utility::internal {

template<std::floating_point ATime>
    requires(std::numeric_limits<ATime>::digits >= std::numeric_limits<double>::digits) // clang-format off
Timer<ATime>::Timer() noexcept :
    fT0(sc::now()) {} // clang-format on

} // namespace MACE::Utility::internal
