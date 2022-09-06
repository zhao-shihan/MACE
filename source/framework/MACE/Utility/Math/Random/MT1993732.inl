namespace MACE::Utility::Math::Random {

constexpr MT1993732::MT1993732() :
    MT1993732(5489U) {}

constexpr MT1993732::MT1993732(MT1993732::ResultType seed) :
    fMT(),
    fTempered(),
    fTemperedEnd(fTempered.cend()),
    fTemperedIterator(fTemperedEnd) {
    Seed(seed);
}

constexpr void MT1993732::Seed(MT1993732::ResultType seed) {
    fMT[0] = seed;
    for (ResultType i = 0; i < 623U; ++i) { // LCG ;)
        fMT[i + 1U] = 0x6c078965U * (fMT[i] ^ fMT[i] >> 30U) + i + 1U;
    }
    // Set iterator
    fTemperedIterator = fTemperedEnd;
}

constexpr MT1993732::ResultType MT1993732::operator()() {
    if (fTemperedIterator == fTemperedEnd) { Regenerate(); }
    return *(fTemperedIterator++);
}

constexpr void MT1993732::Regenerate() {
    ResultType i;
    ResultType x;

    constexpr ResultType magic = 0x9908b0dfU;
    // i = [0 ... 226]
    for (i = 0U; i < 227U; ++i) {
        x = (0x80000000U & fMT[i]) | (0x7fffffffU & fMT[i + 1]);
        fMT[i] = fMT[i + 397U] ^ (x >> 1U) ^ (((std::int32_t(x) << 31) >> 31) & magic);
    }
    // i = [227 ... 622]
    for (; i < 623U; ++i) {
        x = (0x80000000U & fMT[i]) | (0x7fffffffU & fMT[i + 1]);
        fMT[i] = fMT[i - 227U] ^ (x >> 1U) ^ (((std::int32_t(x) << 31) >> 31) & magic);
    }
    // i = 623, wrapping around
    x = (0x80000000U & fMT.back()) | (0x7fffffffU & fMT.front());
    fMT.back() = fMT[396] ^ (x >> 1U) ^ (((std::int32_t(x) << 31) >> 31) & magic);

    // Tempering
    for (i = 0U; i < 624U; ++i) {
        x = fMT[i];
        x ^= x >> 11U;
        x ^= x << 7U & 0x9d2c5680U;
        x ^= x << 15U & 0xefc60000U;
        x ^= x >> 18U;
        fTempered[i] = x;
    }

    // Reset iterator
    fTemperedIterator = fTempered.cbegin();
}

} // namespace MACE::Utility::Math::Random
