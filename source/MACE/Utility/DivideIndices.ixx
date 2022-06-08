namespace MACE::Utility {

template<std::integral Index_t>
std::vector<Index_t> DivideIndexNum(Index_t nIndices, Index_t nTakers) {
    const auto basicDivision = nIndices / nTakers;
    const auto remainder = nIndices % nTakers;
    std::vector<Index_t> dividedIndexNums(nTakers, basicDivision);
    for (Index_t i = 0; i < remainder; ++i) {
        ++dividedIndexNums[i];
    }
    return dividedIndexNums;
}

template<std::integral Index_t>
std::vector<DividedIndexRange<Index_t>> DivideIndexRangeIndexWise(Index_t begin, Index_t end, Index_t nTakers) {
    const auto dividedIndexNums = DivideIndexNum<Index_t>(end - begin, nTakers);
    std::vector<DividedIndexRange<Index_t>> dividedIndexRanges(nTakers);
    for (Index_t i = 0; i < nTakers; ++i) {
        dividedIndexRanges[i] = {i,
                                 i + dividedIndexNums[i] * nTakers,
                                 nTakers,
                                 dividedIndexNums[i]};
    }
    return dividedIndexRanges;
}

template<std::integral Index_t>
std::vector<DividedIndexRange<Index_t>> DivideIndexRangeIndexWise(std::pair<Index_t, Index_t> beginEnd, Index_t nTakers) {
    return DivideIndexRangeIndexWise<Index_t>(beginEnd.first, beginEnd.second, nTakers);
}

template<std::integral Index_t>
std::vector<DividedIndexRange<Index_t>> DivideIndexRangeTakerWise(Index_t begin, Index_t end, Index_t nTakers) {
    const auto dividedIndexNums = DivideIndexNum<Index_t>(end - begin, nTakers);
    std::vector<DividedIndexRange<Index_t>> dividedIndexRanges(nTakers);
    dividedIndexRanges[0] = {(Index_t)0,
                             dividedIndexNums[0],
                             (Index_t)1,
                             dividedIndexNums[0]};
    for (Index_t i = 1; i < nTakers; ++i) {
        dividedIndexRanges[i] = {dividedIndexRanges[i - 1].end,
                                 dividedIndexRanges[i - 1].end + dividedIndexNums[i],
                                 (Index_t)1,
                                 dividedIndexNums[i]};
    }
    return dividedIndexRanges;
}

template<std::integral Index_t>
std::vector<DividedIndexRange<Index_t>> DivideIndexRangeTakerWise(std::pair<Index_t, Index_t> beginEnd, Index_t nTakers) {
    return DivideIndexRangeTakerWise<Index_t>(beginEnd.first, beginEnd.second, nTakers);
}

} // namespace MACE::Utility
