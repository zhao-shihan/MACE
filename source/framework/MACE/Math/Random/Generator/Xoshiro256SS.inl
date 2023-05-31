namespace MACE::Math::Random::inline Generator {

constexpr Xoshiro256SS::Xoshiro256SS(std::uint64_t seed) :
    Xoshiro256Base(seed) {}

MACE_ALWAYS_INLINE constexpr Xoshiro256SS::ResultType Xoshiro256SS::operator()() {
    const auto result = std::rotl(fState[1] * 5, 7) * 9;
    Step();
    return result;
}

} // namespace MACE::Math::Random::inline Generator
