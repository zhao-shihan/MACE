namespace MACE::Utility {

template<std::integral IndexT>
std::vector<IndexT> DivideIndexNum(IndexT nIndices, IndexT nTakers) {
    const auto basicDivision = nIndices / nTakers;
    const auto remainder = nIndices % nTakers;
    std::vector<IndexT> dividedIndexNums(nTakers, basicDivision);
    for (IndexT i = 0; i < remainder; ++i) {
        ++dividedIndexNums[i];
    }
    return dividedIndexNums;
}

template<std::integral IndexT>
std::vector<DividedIndexRange<IndexT>> DivideIndexRangeIndexWise(IndexT begin, IndexT end, IndexT nTakers) {
    const auto dividedIndexNums = DivideIndexNum<IndexT>(end - begin, nTakers);
    std::vector<DividedIndexRange<IndexT>> dividedIndexRanges(nTakers);
    for (IndexT i = 0; i < nTakers; ++i) {
        dividedIndexRanges[i] = {i,
                                 i + dividedIndexNums[i] * nTakers,
                                 nTakers,
                                 dividedIndexNums[i]};
    }
    return dividedIndexRanges;
}

template<std::integral IndexT>
std::vector<DividedIndexRange<IndexT>> DivideIndexRangeIndexWise(std::pair<IndexT, IndexT> beginEnd, IndexT nTakers) {
    return DivideIndexRangeIndexWise<IndexT>(beginEnd.first, beginEnd.second, nTakers);
}

template<std::integral IndexT>
std::vector<DividedIndexRange<IndexT>> DivideIndexRangeTakerWise(IndexT begin, IndexT end, IndexT nTakers) {
    const auto dividedIndexNums = DivideIndexNum<IndexT>(end - begin, nTakers);
    std::vector<DividedIndexRange<IndexT>> dividedIndexRanges(nTakers);
    dividedIndexRanges[0] = {(IndexT)0,
                             dividedIndexNums[0],
                             (IndexT)1,
                             dividedIndexNums[0]};
    for (IndexT i = 1; i < nTakers; ++i) {
        dividedIndexRanges[i] = {dividedIndexRanges[i - 1].end,
                                 dividedIndexRanges[i - 1].end + dividedIndexNums[i],
                                 (IndexT)1,
                                 dividedIndexNums[i]};
    }
    return dividedIndexRanges;
}

template<std::integral IndexT>
std::vector<DividedIndexRange<IndexT>> DivideIndexRangeTakerWise(std::pair<IndexT, IndexT> beginEnd, IndexT nTakers) {
    return DivideIndexRangeTakerWise<IndexT>(beginEnd.first, beginEnd.second, nTakers);
}

} // namespace MACE::Utility
