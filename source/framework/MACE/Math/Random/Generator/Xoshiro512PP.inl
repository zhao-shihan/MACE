namespace MACE::Math::Random::inline Generator {

constexpr Xoshiro512PP::Xoshiro512PP(std::uint64_t seed) :
    Xoshiro512Base(seed) {}

constexpr Xoshiro512PP::ResultType Xoshiro512PP::operator()() {
    const auto result = std::rotl(fState[0] + fState[2], 17) + fState[2];
    Step();
    return result;
}

} // namespace MACE::Math::Random::inline Generator
