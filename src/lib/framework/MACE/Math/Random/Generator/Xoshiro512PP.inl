namespace MACE::Math::Random::inline Generator {

constexpr Xoshiro512PP::Xoshiro512PP(std::uint64_t seed) :
    Xoshiro512Base(seed) {}

constexpr auto Xoshiro512PP::operator()() -> Xoshiro512PP::ResultType {
    const auto result = std::rotl(fState[0] + fState[2], 17) + fState[2];
    Step();
    return result;
}

} // namespace MACE::Math::Random::inline Generator
