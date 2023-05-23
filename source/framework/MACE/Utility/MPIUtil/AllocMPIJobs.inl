namespace MACE::inline Utility::MPIUtil {

template<std::integral AIndex>
IntegralIndexRange<AIndex> AllocMPIJobsJobWise(AIndex jobBegin, AIndex jobEnd, int commSize, int commRank) {
    return DivideIndexRangeIndexWise<AIndex>(jobBegin, jobEnd, commSize)[commRank];
}

template<std::integral AIndex>
IntegralIndexRange<AIndex> AllocMPIJobsJobWise(AIndex jobBegin, AIndex jobEnd, MPI_Comm comm) {
    int commSize;
    int commRank;
    if (const auto& mpiEnv = Env::MPIEnv::Instance();
        comm == MPI_COMM_WORLD) {
        commSize = mpiEnv.CommWorldSize();
        commRank = mpiEnv.CommWorldRank();
    } else if (comm == mpiEnv.CommShared()) {
        commSize = mpiEnv.CommSharedSize();
        commRank = mpiEnv.CommSharedRank();
    } else {
        MACE_MPI_CALL_WITH_CHECK(MPI_Comm_size,
                                 comm,
                                 &commSize)
        MACE_MPI_CALL_WITH_CHECK(MPI_Comm_rank,
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
    if (const auto& mpiEnv = Env::MPIEnv::Instance();
        comm == MPI_COMM_WORLD) {
        commSize = mpiEnv.CommWorldSize();
        commRank = mpiEnv.CommWorldRank();
    } else if (comm == mpiEnv.CommShared()) {
        commSize = mpiEnv.CommSharedSize();
        commRank = mpiEnv.CommSharedRank();
    } else {
        MACE_MPI_CALL_WITH_CHECK(MPI_Comm_size,
                                 comm,
                                 &commSize)
        MACE_MPI_CALL_WITH_CHECK(MPI_Comm_rank,
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

} // namespace MACE::inline Utility::MPIUtil
