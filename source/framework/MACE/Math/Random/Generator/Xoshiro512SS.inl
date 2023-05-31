namespace MACE::Math::Random::inline Generator {

constexpr Xoshiro512SS::Xoshiro512SS(std::uint64_t seed) :
    Xoshiro512Base(seed) {}

MACE_ALWAYS_INLINE constexpr Xoshiro512SS::ResultType Xoshiro512SS::operator()() {
    const auto result = std::rotl(fState[1] * 5, 7) * 9;
    Step();
    return result;
}

} // namespace MACE::Math::Random::inline Generator
