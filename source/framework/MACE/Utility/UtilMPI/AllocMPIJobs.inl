namespace MACE::Utility::UtilMPI {

template<std::integral AIndex>
IntegralIndexRange<AIndex> AllocMPIJobsJobWise(AIndex jobBegin, AIndex jobEnd, int commSize, int commRank) {
    return DivideIndexRangeIndexWise<AIndex>(jobBegin, jobEnd, commSize)[commRank];
}

template<std::integral AIndex>
IntegralIndexRange<AIndex> AllocMPIJobsJobWise(AIndex jobBegin, AIndex jobEnd, MPI_Comm comm) {
    using MACE::Environment::MPIEnvironment;
    if (comm == MPI_COMM_WORLD) {
        return AllocMPIJobsJobWise<AIndex>(jobBegin, jobEnd,
                                           MPIEnvironment::WorldCommSize(), MPIEnvironment::WorldCommRank());
    } else {
        int commRank;
        MPI_Comm_rank(comm, &commRank);
        int commSize;
        MPI_Comm_size(comm, &commSize);
        return AllocMPIJobsJobWise<AIndex>(jobBegin, jobEnd,
                                           commSize, commRank);
    }
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
    using MACE::Environment::MPIEnvironment;
    if (comm == MPI_COMM_WORLD) {
        return AllocMPIJobsWorkerWise<AIndex>(jobBegin, jobEnd,
                                              MPIEnvironment::WorldCommSize(), MPIEnvironment::WorldCommRank());
    } else {
        int commRank;
        MPI_Comm_rank(comm, &commRank);
        int commSize;
        MPI_Comm_size(comm, &commSize);
        return AllocMPIJobsWorkerWise<AIndex>(jobBegin, jobEnd,
                                              commSize, commRank);
    }
}

template<std::integral AIndex>
IntegralIndexRange<AIndex> AllocMPIJobsWorkerWise(std::pair<AIndex, AIndex> jobBeginEnd, MPI_Comm comm) {
    return AllocMPIJobsWorkerWise<AIndex>(jobBeginEnd.first, jobBeginEnd.second, comm);
}

template<std::integral AIndex>
IntegralIndexRange<AIndex> AllocMPIJobsWorkerWise(std::pair<AIndex, AIndex> jobBeginEnd, int commSize, int commRank) {
    return AllocMPIJobsWorkerWise<AIndex>(jobBeginEnd.first, jobBeginEnd.second, commSize, commRank);
}

} // namespace MACE::Utility::UtilMPI
