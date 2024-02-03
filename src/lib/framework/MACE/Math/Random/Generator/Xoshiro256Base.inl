namespace MACE::Math::Random::inline Generator {

template<typename ADerived>
constexpr Xoshiro256Base<ADerived>::Xoshiro256Base() : // clang-format off
    XoshiroBase<ADerived, 256>{{0x893C3E22C678FAA9ull,
                                0x30589ADC78696ADAull,
                                0x1D541511D5F51D5Bull,
                                0xE3CBD397A993A9EEull}} { // clang-format on
    static_assert(std::derived_from<ADerived, Xoshiro256Base<ADerived>>);
}

template<typename ADerived>
constexpr Xoshiro256Base<ADerived>::Xoshiro256Base(std::uint64_t seed) :
    XoshiroBase<ADerived, 256>{seed} {}

template<typename ADerived>
MACE_ALWAYS_INLINE constexpr auto Xoshiro256Base<ADerived>::Step() -> void {
    const auto t{this->fState[1] << 17};

    this->fState[2] ^= this->fState[0];
    this->fState[3] ^= this->fState[1];
    this->fState[1] ^= this->fState[2];
    this->fState[0] ^= this->fState[3];

    this->fState[2] ^= t;

    this->fState[3] = std::rotl(this->fState[3], 45);
}

template<Concept::Character AChar, typename T>
auto operator<<(std::basic_ostream<AChar>& os, const Xoshiro256Base<T>& self) -> decltype(os) {
    return os << self.fState[0] << ' '
              << self.fState[1] << ' '
              << self.fState[2] << ' '
              << self.fState[3];
}

template<Concept::Character AChar, typename T>
auto operator>>(std::basic_istream<AChar>& is, Xoshiro256Base<T>& self) -> decltype(is) {
    return is >> self.fState[0] // clang-format off
              >> self.fState[1]
              >> self.fState[2]
              >> self.fState[3]; // clang-format on
}

} // namespace MACE::Math::Random::inline Generator
