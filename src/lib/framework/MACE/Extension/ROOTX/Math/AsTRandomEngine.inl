namespace MACE::inline Extension::ROOTX::Math {

template<MACE::Math::Random::UniformPseudoRandomBitGenerator PRBG>
AsTRandomEngine<PRBG>::AsTRandomEngine(typename PRBG::SeedType seed) :
    fPRBG{seed} {}

} // namespace MACE::inline Extension::ROOTX::Math
