namespace MACE::Math::Random::inline Generator {

template<class ADerived>
constexpr Xoshiro256Base<ADerived>::Xoshiro256Base() :
    UniformPseudoRandomBitGeneratorBase<ADerived, std::uint64_t>(),
    fState{0x893C3E22C678FAA9ull,
           0x30589ADC78696ADAull,
           0x1D541511D5F51D5Bull,
           0xE3CBD397A993A9EEull} {
    static_assert(std::derived_from<ADerived, Xoshiro256Base<ADerived>>);
    static_assert(std::is_final_v<ADerived>);
}

template<class ADerived>
constexpr Xoshiro256Base<ADerived>::Xoshiro256Base(std::uint64_t seed) :
    UniformPseudoRandomBitGeneratorBase<ADerived, std::uint64_t>(),
    fState() {
    Seed(seed);
}

template<class ADerived>
constexpr void Xoshiro256Base<ADerived>::Step() {
    const auto t = fState[1] << 17;

    fState[2] ^= fState[0];
    fState[3] ^= fState[1];
    fState[1] ^= fState[2];
    fState[0] ^= fState[3];

    fState[2] ^= t;

    fState[3] = std::rotl(fState[3], 45);
}

template<class ADerived>
void Xoshiro256Base<ADerived>::Seed(std::uint64_t seed) {
    SplitMix64 splitMix64(seed);
    std::ranges::generate(fState, splitMix64);
    Step();
    Step();
    Step();
}

template<Concept::Character AChar, class T>
auto operator<<(std::basic_ostream<AChar>& os, const Xoshiro256Base<T>& self) -> decltype(os) {
    return os << self.fState[0] << ' ' << self.fState[1] << ' ' << self.fState[2] << ' ' << self.fState[3];
}

template<Concept::Character AChar, class T>
auto operator>>(std::basic_istream<AChar>& is, Xoshiro256Base<T>& self) -> decltype(is) {
    return is >> self.fState[0] >> self.fState[1] >> self.fState[2] >> self.fState[3];
}

} // namespace MACE::Math::Random::inline Generator
