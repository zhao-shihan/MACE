namespace MACE::Math::Random::inline Generator {

constexpr Xoshiro256Plus::Xoshiro256Plus(std::uint64_t seed) :
    Xoshiro256Base(seed) {}

MACE_ALWAYS_INLINE constexpr auto Xoshiro256Plus::operator()() -> Xoshiro256Plus::ResultType {
    const auto result = fState[0] + fState[3];
    Step();
    return result;
}

} // namespace MACE::Math::Random::inline Generator
