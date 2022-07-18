namespace MACE::Utility {

template<std::integral AIndex>
std::vector<AIndex> DivideIndexNum(AIndex nIndices, AIndex nTakers) {
    const auto basicDivision = nIndices / nTakers;
    const auto remainder = nIndices % nTakers;
    std::vector<AIndex> dividedIndexNums(nTakers, basicDivision);
    for (AIndex i = 0; i < remainder; ++i) {
        ++dividedIndexNums[i];
    }
    return dividedIndexNums;
}

template<std::integral AIndex>
std::vector<IntegralIndexRange<AIndex>> DivideIndexRangeIndexWise(AIndex begin, AIndex end, AIndex nTakers) {
    const auto dividedIndexNums = DivideIndexNum<AIndex>(end - begin, nTakers);
    std::vector<IntegralIndexRange<AIndex>> dividedIndexRanges(nTakers);
    for (AIndex i = 0; i < nTakers; ++i) {
        dividedIndexRanges[i] = {i,
                                 i + dividedIndexNums[i] * nTakers,
                                 nTakers,
                                 dividedIndexNums[i]};
    }
    return dividedIndexRanges;
}

template<std::integral AIndex>
std::vector<IntegralIndexRange<AIndex>> DivideIndexRangeIndexWise(std::pair<AIndex, AIndex> beginEnd, AIndex nTakers) {
    return DivideIndexRangeIndexWise<AIndex>(beginEnd.first, beginEnd.second, nTakers);
}

template<std::integral AIndex>
std::vector<IntegralIndexRange<AIndex>> DivideIndexRangeTakerWise(AIndex begin, AIndex end, AIndex nTakers) {
    const auto dividedIndexNums = DivideIndexNum<AIndex>(end - begin, nTakers);
    std::vector<IntegralIndexRange<AIndex>> dividedIndexRanges(nTakers);
    dividedIndexRanges[0] = {(AIndex)0,
                             dividedIndexNums[0],
                             (AIndex)1,
                             dividedIndexNums[0]};
    for (AIndex i = 1; i < nTakers; ++i) {
        dividedIndexRanges[i] = {dividedIndexRanges[i - 1].end,
                                 dividedIndexRanges[i - 1].end + dividedIndexNums[i],
                                 (AIndex)1,
                                 dividedIndexNums[i]};
    }
    return dividedIndexRanges;
}

template<std::integral AIndex>
std::vector<IntegralIndexRange<AIndex>> DivideIndexRangeTakerWise(std::pair<AIndex, AIndex> beginEnd, AIndex nTakers) {
    return DivideIndexRangeTakerWise<AIndex>(beginEnd.first, beginEnd.second, nTakers);
}

} // namespace MACE::Utility
