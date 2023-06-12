namespace MACE::Math::Random::inline Generator {

constexpr SplitMix64::SplitMix64() :
    UniformPseudoRandomBitGeneratorBase(),
    fState(0x1BCC2859AEA0EE4Dull) {}

constexpr SplitMix64::SplitMix64(SplitMix64::ResultType seed) :
    UniformPseudoRandomBitGeneratorBase(),
    fState() {
    Seed(seed);
}

MACE_ALWAYS_INLINE constexpr auto SplitMix64::operator()() -> SplitMix64::ResultType {
    auto z = (fState += 0x9E3779B97F4A7C15ull);
    z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9ull;
    z = (z ^ (z >> 27)) * 0x94D049BB133111EBull;
    return z ^ (z >> 31);
}

constexpr auto SplitMix64::Seed(SplitMix64::ResultType seed) -> void {
    fState = seed;
    (*this)();
    (*this)();
    (*this)();
}

} // namespace MACE::Math::Random::inline Generator
