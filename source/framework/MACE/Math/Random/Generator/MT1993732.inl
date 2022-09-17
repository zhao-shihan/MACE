namespace MACE::Math::Random::Generator {

constexpr MT1993732::MT1993732() :
    MT1993732(5489U) {}

constexpr MT1993732::MT1993732(MT1993732::ResultType seed) :
    UniformRandomBitGeneratorBase(),
    fMT(),
    fTempered(),
    fTemperedEnd(fTempered + 624U),
    fTemperedIterator(fTemperedEnd) {
    Seed(seed);
}

constexpr MT1993732::ResultType MT1993732::operator()() {
    if (fTemperedIterator == fTemperedEnd) { Regenerate(); }
    return *(fTemperedIterator++);
}

constexpr void MT1993732::Seed(MT1993732::ResultType seed) {
    fMT[0] = seed;
    for (ResultType i = 1U; i < 624U; ++i) { // LCG ;)
        fMT[i] = 0x6c078965U * (fMT[i - 1U] ^ fMT[i - 1U] >> 30U) + i;
    }
    // Set iterator
    fTemperedIterator = fTemperedEnd;
}

constexpr void MT1993732::Regenerate() {
    ResultType i;
    ResultType x;

    constexpr ResultType magic = 0x9908b0dfU;
    // i = [0 ... 226]
    for (i = 0U; i < 227U; ++i) {
        x = (0x80000000U & fMT[i]) | (0x7fffffffU & fMT[i + 1U]);
        fMT[i] = fMT[i + 397U] ^ (x >> 1U) ^ (((static_cast<std::int32_t>(x) << 31) >> 31) & magic);
    }
    // i = [227 ... 622]
    for (; i < 623U; ++i) {
        x = (0x80000000U & fMT[i]) | (0x7fffffffU & fMT[i + 1U]);
        fMT[i] = fMT[i - 227U] ^ (x >> 1U) ^ (((static_cast<std::int32_t>(x) << 31) >> 31) & magic);
    }
    // i = 623, wrapping around
    x = (0x80000000U & fMT[623]) | (0x7fffffffU & fMT[0]);
    fMT[623] = fMT[396] ^ (x >> 1U) ^ (((static_cast<std::int32_t>(x) << 31) >> 31) & magic);

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
    fTemperedIterator = fTempered;
}

} // namespace MACE::Math::Random
