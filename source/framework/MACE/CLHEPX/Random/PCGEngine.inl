namespace MACE::CLHEPX::Random {

inline PCGEngine::PCG::ResultType PCGEngine::NonZeroPCGRandom() {
    PCG::ResultType value;
    do {
        value = fPCG();
    } while (value == 0);
    return value;
}

} // namespace CLHEPX
