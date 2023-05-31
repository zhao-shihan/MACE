namespace MACE::Math::Random::inline Generator {

template<class ADerived>
constexpr Xoshiro512Base<ADerived>::Xoshiro512Base() :
    XoshiroBase<ADerived, 512>({0x893C3E22C678FAA9ull,
                                0x30589ADC78696ADAull,
                                0x1D541511D5F51D5Bull,
                                0xE3CBD397A993A9EEull,
                                0x1A7CB96107B6F389ull,
                                0xD947C32467BF2036ull,
                                0xD7A5E004646E6A58ull,
                                0x6426F7F8732F5C48ull}) {
    static_assert(std::derived_from<ADerived, Xoshiro512Base<ADerived>>);
}

template<class ADerived>
constexpr Xoshiro512Base<ADerived>::Xoshiro512Base(std::uint64_t seed) :
    XoshiroBase<ADerived, 512>(seed) {}

template<class ADerived>
MACE_ALWAYS_INLINE constexpr void Xoshiro512Base<ADerived>::Step() {
    const auto t = this->fState[1] << 11;

    this->fState[2] ^= this->fState[0];
    this->fState[5] ^= this->fState[1];
    this->fState[1] ^= this->fState[2];
    this->fState[7] ^= this->fState[3];
    this->fState[3] ^= this->fState[4];
    this->fState[4] ^= this->fState[5];
    this->fState[0] ^= this->fState[6];
    this->fState[6] ^= this->fState[7];

    this->fState[6] ^= t;

    this->fState[7] = std::rotl(this->fState[7], 21);
}

template<Concept::Character AChar, class T>
auto operator<<(std::basic_ostream<AChar>& os, const Xoshiro512Base<T>& self) -> decltype(os) {
    return os << self.fState[0] << ' '
              << self.fState[1] << ' '
              << self.fState[2] << ' '
              << self.fState[3] << ' '
              << self.fState[4] << ' '
              << self.fState[5] << ' '
              << self.fState[6] << ' '
              << self.fState[7];
}

template<Concept::Character AChar, class T>
auto operator>>(std::basic_istream<AChar>& is, Xoshiro512Base<T>& self) -> decltype(is) {
    return is >> self.fState[0] // clang-format off
              >> self.fState[1]
              >> self.fState[2]
              >> self.fState[3]
              >> self.fState[4]
              >> self.fState[5]
              >> self.fState[6]
              >> self.fState[7]; // clang-format on
}

} // namespace MACE::Math::Random::inline Generator
