namespace MACE::Math::Random::Generator {

constexpr PCGXSHRR6432::PCGXSHRR6432() :
    UniformRandomBitGeneratorBase(),
    fState(0x853c49e6748fea9bULL) {}

constexpr PCGXSHRR6432::PCGXSHRR6432(PCGXSHRR6432::StateType seed) :
    UniformRandomBitGeneratorBase(),
    fState() {
    Seed(seed);
}

constexpr PCGXSHRR6432::ResultType PCGXSHRR6432::operator()() {
    const auto s = fState;
    Step();
    return std::rotr<ResultType>(((s >> 18U) ^ s) >> 27U, s >> 59U);
}

constexpr void PCGXSHRR6432::Seed(PCGXSHRR6432::StateType seed) {
    fState = 0U;
    Step();
    fState += seed;
    Step();
}

constexpr void PCGXSHRR6432::Discard(PCGXSHRR6432::StateType n) {
    StateType currentMultipiler = Multipiler();
    StateType currentIncrement = Increment();
    StateType accelerateMultipiler = 1U;
    StateType accelerateIncrement = 0U;
    while (n > 0) {
        if (IsOdd(n)) {
            accelerateMultipiler *= currentMultipiler;
            accelerateIncrement = accelerateIncrement * currentMultipiler + currentIncrement;
        }
        currentIncrement *= (currentMultipiler + 1);
        currentMultipiler *= currentMultipiler;
        n /= 2;
    }
    fState = accelerateMultipiler * fState + accelerateIncrement;
}

} // namespace MACE::Math::Random
