#pragma once

#include <concepts>
#include <vector>

namespace MACE::Utility {

/// @brief Distribute numbers uniformly to takers.
/// @param nIndices Total number of index
/// @param nTakers Number of takers
/// @return Number of indices allocate for each takers.
/// e.g. nIndices = 74, nTakers = 7,
///   taker 0: 11
///   taker 1: 11
///   taker 2: 11
///   taker 3: 11
///   taker 4: 10
///   taker 5: 10
///   taker 6: 10
template<std::integral IndexT>
std::vector<IndexT> DivideIndexNum(IndexT nIndices, IndexT nTakers);

/// @brief The return struct of DivideIndexRange... functions.
template<std::integral IndexT>
struct IntegralIndexRange {
    IndexT begin; // the first index
    IndexT end;   // index after the last index
    IndexT step;  // increment of index
    IndexT count; // total num of indices of this division
};

/// @brief Distribute index range uniformly to workers.
/// The range assigned to each taker are not continuous, but taker are continuous according to the order of indices.
/// @param begin Index of first job
/// @param end Index after the last job
/// @param nTakers Number of workers
/// @return [job index begin, job index end, job index step] for each worker.
/// e.g. nIndices = 74, nTakers = 7,
///   taker 0: [0, 77, 7, 11]
///   taker 1: [1, 78, 7, 11]
///   taker 2: [2, 79, 7, 11]
///   taker 3: [3, 80, 7, 11]
///   taker 4: [4, 74, 7, 10]
///   taker 5: [5, 75, 7, 10]
///   taker 6: [6, 76, 7, 10]
template<std::integral IndexT>
std::vector<IntegralIndexRange<IndexT>> DivideIndexRangeIndexWise(IndexT begin, IndexT end, IndexT nTakers);
template<std::integral IndexT>
std::vector<IntegralIndexRange<IndexT>> DivideIndexRangeIndexWise(std::pair<IndexT, IndexT> beginEnd, IndexT nTakers);

/// @brief Distribute index range uniformly to takers. The range assigned to each taker are continuous.
/// @param begin Index of first job
/// @param end Index after the last job
/// @param nTakers Number of workers
/// @return [job index begin, job index end, job index step] for each worker.
/// e.g. nIndices = 74, nTakers = 7,
///   taker 0: [0, 11, 1, 11]
///   taker 1: [11, 22, 1, 11]
///   taker 2: [22, 33, 1, 11]
///   taker 3: [33, 44, 1, 11]
///   taker 4: [44, 54, 1, 10]
///   taker 5: [54, 64, 1, 10]
///   taker 6: [64, 74, 1, 10]
template<std::integral IndexT>
std::vector<IntegralIndexRange<IndexT>> DivideIndexRangeTakerWise(IndexT begin, IndexT end, IndexT nTakers);
template<std::integral IndexT>
std::vector<IntegralIndexRange<IndexT>> DivideIndexRangeTakerWise(std::pair<IndexT, IndexT> beginEnd, IndexT nTakers);

} // namespace MACE::Utility

#include "MACE/Utility/DivideIndices.inl"
