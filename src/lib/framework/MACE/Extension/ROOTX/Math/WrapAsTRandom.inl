namespace MACE::inline Extension::ROOTX::Math {

template<MACE::Math::Random::UniformPseudoRandomBitGenerator PRBG>
WrapAsTRandom<PRBG>::WrapAsTRandom(typename PRBG::SeedType seed) :
    fPRBG{seed},
    fGaussian{} {}

template<MACE::Math::Random::UniformPseudoRandomBitGenerator PRBG>
auto WrapAsTRandom<PRBG>::RndmArray(Int_t n, Float_t* array) -> void {
    std::ranges::generate_n(array, n, [this] { return MACE::Math::Random::Uniform<Float_t>{}(fPRBG); });
}

template<MACE::Math::Random::UniformPseudoRandomBitGenerator PRBG>
auto WrapAsTRandom<PRBG>::RndmArray(Int_t n, Double_t* array) -> void {
    std::ranges::generate_n(array, n, [this] { return Rndm(); });
}

template<MACE::Math::Random::UniformPseudoRandomBitGenerator PRBG>
auto WrapAsTRandom<PRBG>::GetSeed() const -> UInt_t {
    fmt::println(stderr, "WrapAsTRandom<PRBG>::GetSeed has no effect. Do not use");
    return 0;
}

} // namespace MACE::inline Extension::ROOTX::Math
