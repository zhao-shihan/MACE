#pragma once

#include "MACE/Env/MPIEnv.h++"
#include "MACE/Utility/DivideIndices.h++"
#include "MACE/Utility/MPIUtil/MPICallWithCheck.h++"

#include "mpi.h"

#include <concepts>
#include <utility>

namespace MACE::inline Utility::MPIUtil {

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

} // namespace MACE::inline Utility::MPIUtil

#include "MACE/Utility/MPIUtil/AllocMPIJobs.inl"
