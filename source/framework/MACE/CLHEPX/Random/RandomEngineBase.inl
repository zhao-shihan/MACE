namespace MACE::CLHEPX::Random {

template<Math::Random::UniformPseudoRandomBitGenerator PRBG>
RandomEngineBase<PRBG>::RandomEngineBase() :
    HepRandomEngine(),
    fPRBG() {
    static_assert(std::is_final_v<PRBG>);
    static_assert(std::derived_from<PRBG, RandomEngineBase<PRBG>>);
    constexpr long seedMin = 1;
    constexpr long seedMax = std::numeric_limits<long>::max() - 1;
    Math::Random::Generator::PCGXSHRR6432 pcg32(reinterpret_cast<std::uintptr_t>(this));
    setSeed(Math::Random::Distribution::Uniform<long>(seedMin, seedMax)(pcg32));
}

template<Math::Random::UniformPseudoRandomBitGenerator PRBG>
RandomEngineBase<PRBG>::RandomEngineBase(long seed) :
    HepRandomEngine(),
    fPRBG(seed) {
    theSeed = seed;
    theSeeds = &theSeed;
}

template<Math::Random::UniformPseudoRandomBitGenerator PRBG>
void RandomEngineBase<PRBG>::flatArray(const int size, double* vect) {
    for (int i = 0; i < size; ++i) {
        vect[i] = flat();
    }
}

template<Math::Random::UniformPseudoRandomBitGenerator PRBG>
void RandomEngineBase<PRBG>::setSeed(long seed, int) {
    fPRBG.Seed(seed);
    theSeed = seed;
    theSeeds = &theSeed;
}

template<Math::Random::UniformPseudoRandomBitGenerator PRBG>
void RandomEngineBase<PRBG>::setSeeds(const long* seeds, int) {
    fPRBG.Seed(*seeds);
    theSeed = *seeds;
    theSeeds = seeds;
}

template<Math::Random::UniformPseudoRandomBitGenerator PRBG>
void RandomEngineBase<PRBG>::saveStatus(gsl::czstring filename) const {
    std::ofstream os(filename, std::ios::out);
    if (os.is_open()) {
        put(os);
        os.close();
    } else {
        std::cerr << "RandomEngineBase<PRBG>::saveStatus (with PRBG = " << typeid(PRBG).name() << "): Cannot open \"" << filename << "\", nothing was done\n";
    }
}

template<Math::Random::UniformPseudoRandomBitGenerator PRBG>
void RandomEngineBase<PRBG>::restoreStatus(gsl::czstring filename) {
    std::ifstream is(filename, std::ios::in);
    if (is.is_open()) {
        get(is);
        is.close();
    } else {
        std::cerr << "RandomEngineBase<PRBG>::restoreStatus (with PRBG = " << typeid(PRBG).name() << "): Cannot open \"" << filename << "\", nothing was done\n";
    }
}

template<Math::Random::UniformPseudoRandomBitGenerator PRBG>
void RandomEngineBase<PRBG>::showStatus() const {
    constexpr std::string_view split = "----------------------------------------------------------------";
    const auto engineName = name();
    const auto firstSplit = static_cast<std::intmax_t>(split.length()) -         // length(split) -
                            static_cast<std::intmax_t>(engineName.length() + 9); // length(" " + engineName + " status ")
    const auto firstSplitL = std::max<std::intmax_t>(3, firstSplit / 2);
    const auto firstSplitR = std::max<std::intmax_t>(3, Math::IsEven(firstSplit) ? firstSplitL : (firstSplitL + 1));
    std::cout << std::string(firstSplitL, '-') << ' ' << engineName << " status " << std::string(firstSplitR, '-') << '\n'
              << "Initial seed: " << theSeed << '\n'
              << "Current state: " << fPRBG << '\n'
              << split << std::endl;
}

template<Math::Random::UniformPseudoRandomBitGenerator PRBG>
std::ostream& RandomEngineBase<PRBG>::put(std::ostream& os) const {
    const auto engineName = name();
    os << engineName << "-begin\n"
       << fPRBG << '\n'
       << engineName << "-end\n";
    return os;
}

template<Math::Random::UniformPseudoRandomBitGenerator PRBG>
std::istream& RandomEngineBase<PRBG>::get(std::istream& is) {
    const auto engineName = name();
    std::string tag;
    is >> tag;
    if (tag != std::string(engineName).append("-begin")) {
        std::cerr << "RandomEngineBase<PRBG>::get (with PRBG = " << typeid(PRBG).name() << "): No " << engineName << " found at current position, engine state unchanged. Input stream has been consumed\n";
        return is;
    }
    PRBG volunteer;
    is >> volunteer >> tag;
    if (tag != std::string(engineName).append("-end")) {
        std::cerr << "RandomEngineBase<PRBG>::get (with PRBG = " << typeid(PRBG).name() << "): " << engineName << " read from the input stream is incomplete, engine state unchanged. Input stream has been consumed\n";
        return is;
    }
    fPRBG = volunteer;
    return is;
}

template<Math::Random::UniformPseudoRandomBitGenerator PRBG>
std::istream& RandomEngineBase<PRBG>::getState(std::istream& is) {
    std::cerr << "RandomEngineBase<PRBG>::getState has no effect. Do not use\n";
    return is;
}

} // namespace MACE::CLHEPX::Random
