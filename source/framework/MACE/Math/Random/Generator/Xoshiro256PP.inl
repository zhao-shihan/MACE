namespace MACE::Math::Random::inline Generator {

constexpr Xoshiro256PP::Xoshiro256PP(std::uint64_t seed) :
    Xoshiro256Base(seed) {}

MACE_ALWAYS_INLINE constexpr Xoshiro256PP::ResultType Xoshiro256PP::operator()() {
    const auto result = std::rotl(fState[0] + fState[3], 23) + fState[0];
    Step();
    return result;
}

} // namespace MACE::Math::Random::inline Generator
