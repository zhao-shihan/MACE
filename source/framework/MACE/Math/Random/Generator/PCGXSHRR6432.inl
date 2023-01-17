namespace MACE::Math::Random::Generator {

constexpr PCGXSHRR6432::PCGXSHRR6432() :
    UniformPseudoRandomBitGeneratorBase(),
    fState(0x853C49E6748FEA9Bull) {}

constexpr PCGXSHRR6432::PCGXSHRR6432(PCGXSHRR6432::StateType seed) :
    UniformPseudoRandomBitGeneratorBase(),
    fState() {
    Seed(seed);
}

constexpr PCGXSHRR6432::ResultType PCGXSHRR6432::operator()() {
    const auto s = fState;
    Step();
    return std::rotr<ResultType>(((s >> 18u) ^ s) >> 27u, s >> 59u);
}

constexpr void PCGXSHRR6432::Seed(PCGXSHRR6432::StateType seed) {
    fState = 0u;
    Step();
    fState += seed;
    Step();
}

constexpr void PCGXSHRR6432::Discard(PCGXSHRR6432::StateType n) {
    StateType currentMultipiler = Multipiler();
    StateType currentIncrement = Increment();
    StateType accelerateMultipiler = 1u;
    StateType accelerateIncrement = 0u;
    while (n > 0) {
        if (IsOdd(n)) {
            accelerateMultipiler *= currentMultipiler;
            accelerateIncrement = accelerateIncrement * currentMultipiler + currentIncrement;
        }
        currentIncrement *= (currentMultipiler + 1u);
        currentMultipiler *= currentMultipiler;
        n /= 2u;
    }
    fState = accelerateMultipiler * fState + accelerateIncrement;
}

} // namespace MACE::Math::Random::Generator
