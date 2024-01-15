namespace MACE::inline Extension::ROOTX::Math {

template<MACE::Math::Random::UniformPseudoRandomBitGenerator PRBG>
WrapAsTRandomEngine<PRBG>::WrapAsTRandomEngine(typename PRBG::SeedType seed) :
    fPRBG{seed} {}

} // namespace MACE::inline Extension::ROOTX::Math
