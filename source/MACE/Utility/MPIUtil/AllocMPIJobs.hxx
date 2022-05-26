#pragma once

#include "MACE/Utility/DivideIndices.hxx"
#include "MACE/Utility/MPIUtil/CommonMPIWrapper.hxx"

#include <concepts>
#include <utility>

namespace MACE::Utility::MPIUtil {

template<std::integral Index_t>
DividedIndexRange<Index_t> AllocMPIJobsJobWise(Index_t jobBegin, Index_t jobEnd, MPI_Comm comm);
template<std::integral Index_t>
DividedIndexRange<Index_t> AllocMPIJobsJobWise(Index_t jobBegin, Index_t jobEnd, int commSize, int commRank);
template<std::integral Index_t>
DividedIndexRange<Index_t> AllocMPIJobsJobWise(std::pair<Index_t, Index_t> jobBeginEnd, MPI_Comm comm);
template<std::integral Index_t>
DividedIndexRange<Index_t> AllocMPIJobsJobWise(std::pair<Index_t, Index_t> jobBeginEnd, int commSize, int commRank);

template<std::integral Index_t>
DividedIndexRange<Index_t> AllocMPIJobsWorkerWise(Index_t jobBegin, Index_t jobEnd, MPI_Comm comm);
template<std::integral Index_t>
DividedIndexRange<Index_t> AllocMPIJobsWorkerWise(Index_t jobBegin, Index_t jobEnd, int commSize, int commRank);
template<std::integral Index_t>
DividedIndexRange<Index_t> AllocMPIJobsWorkerWise(std::pair<Index_t, Index_t> jobBeginEnd, MPI_Comm comm);
template<std::integral Index_t>
DividedIndexRange<Index_t> AllocMPIJobsWorkerWise(std::pair<Index_t, Index_t> jobBeginEnd, int commSize, int commRank);

} // namespace MACE::Utility::MPIUtil

#include "MACE/Utility/MPIUtil/AllocMPIJobs.ixx"
