namespace MACE::Math::Random {

template<class ADerived, std::unsigned_integral AResult>
constexpr UniformPseudoRandomBitGeneratorBase<ADerived, AResult>::UniformPseudoRandomBitGeneratorBase() :
    UniformRandomBitGeneratorBase<ADerived, AResult>() {
    static_assert(UniformPseudoRandomBitGenerator<ADerived>);
}

} // namespace MACE::Math::Random
