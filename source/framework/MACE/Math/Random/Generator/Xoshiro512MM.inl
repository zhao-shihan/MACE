namespace MACE::Math::Random::inline Generator {

constexpr Xoshiro512MM::Xoshiro512MM(std::uint64_t seed) :
    Xoshiro512Base(seed) {}

MACE_ALWAYS_INLINE constexpr Xoshiro512MM::ResultType Xoshiro512MM::operator()() {
    const auto result = std::rotl(fState[1] * 5, 7) * 9;
    Step();
    return result;
}

} // namespace MACE::Math::Random::inline Generator
