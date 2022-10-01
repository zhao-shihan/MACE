namespace MACE::Utility::MPIUtil {

template<std::integral AIndex>
IntegralIndexRange<AIndex> AllocMPIJobsJobWise(AIndex jobBegin, AIndex jobEnd, int commSize, int commRank) {
    return DivideIndexRangeIndexWise<AIndex>(jobBegin, jobEnd, commSize)[commRank];
}

template<std::integral AIndex>
IntegralIndexRange<AIndex> AllocMPIJobsJobWise(AIndex jobBegin, AIndex jobEnd, MPI_Comm comm) {
    int commSize;
    int commRank;
    if (const auto& mpiEnv = Environment::MPIEnvironment::Instance();
        comm == MPI_COMM_WORLD) {
        commSize = mpiEnv.WorldCommSize();
        commRank = mpiEnv.WorldCommRank();
    } else if (comm == mpiEnv.LocalComm()) {
        commSize = mpiEnv.LocalCommSize();
        commRank = mpiEnv.LocalCommRank();
    } else {
        MACE_CHECKED_MPI_CALL(MPI_Comm_size,
                              comm,
                              &commSize)
        MACE_CHECKED_MPI_CALL(MPI_Comm_rank,
                              comm,
                              &commRank)
    }
    return AllocMPIJobsJobWise<AIndex>(jobBegin, jobEnd, commSize, commRank);
}

template<std::integral AIndex>
IntegralIndexRange<AIndex> AllocMPIJobsJobWise(std::pair<AIndex, AIndex> jobBeginEnd, int commSize, int commRank) {
    return AllocMPIJobsJobWise<AIndex>(jobBeginEnd.first, jobBeginEnd.second, commSize, commRank);
}

template<std::integral AIndex>
IntegralIndexRange<AIndex> AllocMPIJobsJobWise(std::pair<AIndex, AIndex> jobBeginEnd, MPI_Comm comm) {
    return AllocMPIJobsJobWise<AIndex>(jobBeginEnd.first, jobBeginEnd.second, comm);
}

template<std::integral AIndex>
IntegralIndexRange<AIndex> AllocMPIJobsWorkerWise(AIndex jobBegin, AIndex jobEnd, int commSize, int commRank) {
    return DivideIndexRangeTakerWise<AIndex>(jobBegin, jobEnd, commSize)[commRank];
}

template<std::integral AIndex>
IntegralIndexRange<AIndex> AllocMPIJobsWorkerWise(AIndex jobBegin, AIndex jobEnd, MPI_Comm comm) {
    int commSize;
    int commRank;
    if (const auto& mpiEnv = Environment::MPIEnvironment::Instance();
        comm == MPI_COMM_WORLD) {
        commSize = mpiEnv.WorldCommSize();
        commRank = mpiEnv.WorldCommRank();
    } else if (comm == mpiEnv.LocalComm()) {
        commSize = mpiEnv.LocalCommSize();
        commRank = mpiEnv.LocalCommRank();
    } else {
        MACE_CHECKED_MPI_CALL(MPI_Comm_size,
                              comm,
                              &commSize)
        MACE_CHECKED_MPI_CALL(MPI_Comm_rank,
                              comm,
                              &commRank)
    }
    return AllocMPIJobsWorkerWise<AIndex>(jobBegin, jobEnd, commSize, commRank);
}

template<std::integral AIndex>
IntegralIndexRange<AIndex> AllocMPIJobsWorkerWise(std::pair<AIndex, AIndex> jobBeginEnd, MPI_Comm comm) {
    return AllocMPIJobsWorkerWise<AIndex>(jobBeginEnd.first, jobBeginEnd.second, comm);
}

template<std::integral AIndex>
IntegralIndexRange<AIndex> AllocMPIJobsWorkerWise(std::pair<AIndex, AIndex> jobBeginEnd, int commSize, int commRank) {
    return AllocMPIJobsWorkerWise<AIndex>(jobBeginEnd.first, jobBeginEnd.second, commSize, commRank);
}

} // namespace MACE::Utility::MPIUtil
