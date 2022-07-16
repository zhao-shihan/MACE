#pragma once

#include "MACE/Environment/MPIEnvironment.hxx"
#include "MACE/Utility/DivideIndices.hxx"

#include "mpi.h"

#include <concepts>
#include <utility>

namespace MACE::Utility::MPIUtil {

template<std::integral IndexT>
IntegralIndexRange<IndexT> AllocMPIJobsJobWise(IndexT jobBegin, IndexT jobEnd, int commSize, int commRank);
template<std::integral IndexT>
IntegralIndexRange<IndexT> AllocMPIJobsJobWise(IndexT jobBegin, IndexT jobEnd, MPI_Comm comm);
template<std::integral IndexT>
IntegralIndexRange<IndexT> AllocMPIJobsJobWise(std::pair<IndexT, IndexT> jobBeginEnd, int commSize, int commRank);
template<std::integral IndexT>
IntegralIndexRange<IndexT> AllocMPIJobsJobWise(std::pair<IndexT, IndexT> jobBeginEnd, MPI_Comm comm);

template<std::integral IndexT>
IntegralIndexRange<IndexT> AllocMPIJobsWorkerWise(IndexT jobBegin, IndexT jobEnd, int commSize, int commRank);
template<std::integral IndexT>
IntegralIndexRange<IndexT> AllocMPIJobsWorkerWise(IndexT jobBegin, IndexT jobEnd, MPI_Comm comm);
template<std::integral IndexT>
IntegralIndexRange<IndexT> AllocMPIJobsWorkerWise(std::pair<IndexT, IndexT> jobBeginEnd, int commSize, int commRank);
template<std::integral IndexT>
IntegralIndexRange<IndexT> AllocMPIJobsWorkerWise(std::pair<IndexT, IndexT> jobBeginEnd, MPI_Comm comm);

} // namespace MACE::Utility::MPIUtil

#include "MACE/Utility/MPIUtil/AllocMPIJobs.inl"
