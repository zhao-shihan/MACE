#pragma once

#include "MACE/Environment/MPIEnvironment.hxx"
#include "MACE/Utility/DivideIndices.hxx"
#include "MACE/Utility/MPIUtil/CheckedMPICall.hxx"

#include "mpi.h"

#include <concepts>
#include <utility>

namespace MACE::Utility::MPIUtil {

template<std::integral AIndex>
IntegralIndexRange<AIndex> AllocMPIJobsJobWise(AIndex jobBegin, AIndex jobEnd, int commSize, int commRank);
template<std::integral AIndex>
IntegralIndexRange<AIndex> AllocMPIJobsJobWise(AIndex jobBegin, AIndex jobEnd, MPI_Comm comm);
template<std::integral AIndex>
IntegralIndexRange<AIndex> AllocMPIJobsJobWise(std::pair<AIndex, AIndex> jobBeginEnd, int commSize, int commRank);
template<std::integral AIndex>
IntegralIndexRange<AIndex> AllocMPIJobsJobWise(std::pair<AIndex, AIndex> jobBeginEnd, MPI_Comm comm);

template<std::integral AIndex>
IntegralIndexRange<AIndex> AllocMPIJobsWorkerWise(AIndex jobBegin, AIndex jobEnd, int commSize, int commRank);
template<std::integral AIndex>
IntegralIndexRange<AIndex> AllocMPIJobsWorkerWise(AIndex jobBegin, AIndex jobEnd, MPI_Comm comm);
template<std::integral AIndex>
IntegralIndexRange<AIndex> AllocMPIJobsWorkerWise(std::pair<AIndex, AIndex> jobBeginEnd, int commSize, int commRank);
template<std::integral AIndex>
IntegralIndexRange<AIndex> AllocMPIJobsWorkerWise(std::pair<AIndex, AIndex> jobBeginEnd, MPI_Comm comm);

} // namespace MACE::Utility::MPIUtil

#include "MACE/Utility/MPIUtil/AllocMPIJobs.inl"
