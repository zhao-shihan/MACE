namespace MACE::Math::Random::inline Generator {

constexpr Xoshiro512Plus::Xoshiro512Plus(std::uint64_t seed) :
    Xoshiro512Base(seed) {}

constexpr Xoshiro512Plus::ResultType Xoshiro512Plus::operator()() {
    const auto result = fState[0] + fState[2];
    Step();
    return result;
}

} // namespace MACE::Math::Random::inline Generator
