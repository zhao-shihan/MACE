namespace MACE::Utility {

template<std::integral Index_t>
std::vector<Index_t> DivideIndexNum(Index_t nIndices, Index_t nTaker) {
    const auto basicDivision = nIndices / nTaker;
    const auto remainder = nIndices % nTaker;
    std::vector<Index_t> dividedIndexNums(nTaker, basicDivision);
    for (Index_t i = 0; i < remainder; ++i) {
        ++dividedIndexNums[i];
    }
    return dividedIndexNums;
}

template<std::integral Index_t>
std::vector<DividedIndexRange<Index_t>> DivideIndexRangeIndexWise(Index_t begin, Index_t end, Index_t nTaker) {
    const auto dividedIndexNums = DivideIndexNum<Index_t>(end - begin, nTaker);
    std::vector<DividedIndexRange<Index_t>> dividedIndexRanges(nTaker);
    for (Index_t i = 0; i < nTaker; ++i) {
        dividedIndexRanges[i] = {i,
                                 i + dividedIndexNums[i] * nTaker,
                                 nTaker,
                                 dividedIndexNums[i]};
    }
    return dividedIndexRanges;
}

template<std::integral Index_t>
std::vector<DividedIndexRange<Index_t>> DivideIndexRangeIndexWise(std::pair<Index_t, Index_t> beginEnd, Index_t nTakers) {
    return DivideIndexRangeIndexWise<Index_t>(beginEnd.first, beginEnd.second, nTakers);
}

template<std::integral Index_t>
std::vector<DividedIndexRange<Index_t>> DivideIndexRangeTakerWise(Index_t begin, Index_t end, Index_t nTaker) {
    const auto dividedIndexNums = DivideIndexNum<Index_t>(end - begin, nTaker);
    std::vector<DividedIndexRange<Index_t>> dividedIndexRanges(nTaker);
    dividedIndexRanges[0] = {(Index_t)0,
                             dividedIndexNums[0],
                             (Index_t)1,
                             dividedIndexNums[0]};
    for (Index_t i = 1; i < nTaker; ++i) {
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
