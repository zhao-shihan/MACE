namespace MACE::CLHEPX::Random {

inline OptimizedMTEngine::MT::ResultType OptimizedMTEngine::NonZeroMTRandom() {
    MT::ResultType value;
    do {
        value = fMT();
    } while (value == 0);
    return value;
}

} // namespace CLHEPX
