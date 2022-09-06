namespace MACE::Utility::Math::Random {

constexpr PCGXSHRR6432::PCGXSHRR6432() :
    fState(0x853c49e6748fea9bULL) {}

constexpr PCGXSHRR6432::PCGXSHRR6432(PCGXSHRR6432::StateType seed) :
    fState() {
    Seed(seed);
}

constexpr void PCGXSHRR6432::Seed(PCGXSHRR6432::StateType seed) {
    fState = 0U;
    Step();
    fState += seed;
    Step();
}

constexpr PCGXSHRR6432::ResultType PCGXSHRR6432::operator()() {
    const auto s = fState;
    Step();
    return std::rotr<ResultType>(((s >> 18U) ^ s) >> 27U, s >> 59U);
}

constexpr void PCGXSHRR6432::Discard(PCGXSHRR6432::StateType n) {
    StateType currentMultipiler = fgMultipiler;
    StateType currentIncrement = fgIncrement;
    StateType acceleratedMultipiler = 1U;
    StateType acceleratedIncrement = 0U;
    while (n > 0) {
        if (n & 1) {
            acceleratedMultipiler *= currentMultipiler;
            acceleratedIncrement = acceleratedIncrement * currentMultipiler + currentIncrement;
        }
        currentIncrement *= (currentMultipiler + 1);
        currentMultipiler *= currentMultipiler;
        n /= 2;
    }
    fState = acceleratedMultipiler * fState + acceleratedIncrement;
}

} // namespace MACE::Utility::Math::Random
