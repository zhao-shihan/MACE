#pragma once

#include "MACE/Utility/DivideIndices.hxx"
#include "MACE/Utility/MPIUtil/CommonMPIWrapper.hxx"

#include <concepts>
#include <utility>

namespace MACE::Utility::MPIUtil {

template<std::integral IndexT>
DividedIndexRange<IndexT> AllocMPIJobsJobWise(IndexT jobBegin, IndexT jobEnd, MPI_Comm comm);
template<std::integral IndexT>
DividedIndexRange<IndexT> AllocMPIJobsJobWise(IndexT jobBegin, IndexT jobEnd, int commSize, int commRank);
template<std::integral IndexT>
DividedIndexRange<IndexT> AllocMPIJobsJobWise(std::pair<IndexT, IndexT> jobBeginEnd, MPI_Comm comm);
template<std::integral IndexT>
DividedIndexRange<IndexT> AllocMPIJobsJobWise(std::pair<IndexT, IndexT> jobBeginEnd, int commSize, int commRank);

template<std::integral IndexT>
DividedIndexRange<IndexT> AllocMPIJobsWorkerWise(IndexT jobBegin, IndexT jobEnd, MPI_Comm comm);
template<std::integral IndexT>
DividedIndexRange<IndexT> AllocMPIJobsWorkerWise(IndexT jobBegin, IndexT jobEnd, int commSize, int commRank);
template<std::integral IndexT>
DividedIndexRange<IndexT> AllocMPIJobsWorkerWise(std::pair<IndexT, IndexT> jobBeginEnd, MPI_Comm comm);
template<std::integral IndexT>
DividedIndexRange<IndexT> AllocMPIJobsWorkerWise(std::pair<IndexT, IndexT> jobBeginEnd, int commSize, int commRank);

} // namespace MACE::Utility::MPIUtil

#include "MACE/Utility/MPIUtil/AllocMPIJobs.ixx"
