namespace MACE::Math::Random {

template<typename ADerived,
         std::unsigned_integral AResult>
constexpr UniformRandomBitGeneratorBase<ADerived,
                                        AResult>::UniformRandomBitGeneratorBase() {
    static_assert(UniformRandomBitGenerator<ADerived>);
}

} // namespace MACE::Math::Random
