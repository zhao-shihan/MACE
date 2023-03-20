namespace MACE::Math::Random::Generator {

template<class ADerived>
constexpr Xoshiro256Base<ADerived>::Xoshiro256Base() :
    UniformPseudoRandomBitGeneratorBase<ADerived, std::uint64_t>(),
    fState{14514284786278117030ull,
           4620546740167642908ull,
           13109570281517897720ull,
           17462938647148434322ull} {
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
    std::array<std::uint32_t, 8> s;

    std::minstd_rand lcg(seed);
    std::ranges::generate_n(s.begin(), 4, lcg);

    lcg.seed(seed >> 32);
    std::ranges::generate_n(s.begin() + 4, 4, lcg);

    fState = std::bit_cast<decltype(fState)>(s);

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

} // namespace MACE::Math::Random::Generator
