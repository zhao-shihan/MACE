namespace MACE::Utility::MPIUtil {

template<std::integral IndexT>
IntegralIndexRange<IndexT> AllocMPIJobsJobWise(IndexT jobBegin, IndexT jobEnd, int commSize, int commRank) {
    return DivideIndexRangeIndexWise<IndexT>(jobBegin, jobEnd, commSize)[commRank];
}

template<std::integral IndexT>
IntegralIndexRange<IndexT> AllocMPIJobsJobWise(IndexT jobBegin, IndexT jobEnd, MPI_Comm comm) {
    using MACE::Environment::MPIEnvironment;
    if (comm == MPI_COMM_WORLD) {
        return AllocMPIJobsJobWise<IndexT>(jobBegin, jobEnd,
                                           MPIEnvironment::WorldCommSize(), MPIEnvironment::WorldCommRank());
    } else {
        int commRank;
        MPI_Comm_rank(comm, &commRank);
        int commSize;
        MPI_Comm_size(comm, &commSize);
        return AllocMPIJobsJobWise<IndexT>(jobBegin, jobEnd,
                                           commSize, commRank);
    }
}

template<std::integral IndexT>
IntegralIndexRange<IndexT> AllocMPIJobsJobWise(std::pair<IndexT, IndexT> jobBeginEnd, int commSize, int commRank) {
    return AllocMPIJobsJobWise<IndexT>(jobBeginEnd.first, jobBeginEnd.second, commSize, commRank);
}

template<std::integral IndexT>
IntegralIndexRange<IndexT> AllocMPIJobsJobWise(std::pair<IndexT, IndexT> jobBeginEnd, MPI_Comm comm) {
    return AllocMPIJobsJobWise<IndexT>(jobBeginEnd.first, jobBeginEnd.second, comm);
}

template<std::integral IndexT>
IntegralIndexRange<IndexT> AllocMPIJobsWorkerWise(IndexT jobBegin, IndexT jobEnd, int commSize, int commRank) {
    return DivideIndexRangeTakerWise<IndexT>(jobBegin, jobEnd, commSize)[commRank];
}

template<std::integral IndexT>
IntegralIndexRange<IndexT> AllocMPIJobsWorkerWise(IndexT jobBegin, IndexT jobEnd, MPI_Comm comm) {
    using MACE::Environment::MPIEnvironment;
    if (comm == MPI_COMM_WORLD) {
        return AllocMPIJobsWorkerWise<IndexT>(jobBegin, jobEnd,
                                              MPIEnvironment::WorldCommSize(), MPIEnvironment::WorldCommRank());
    } else {
        int commRank;
        MPI_Comm_rank(comm, &commRank);
        int commSize;
        MPI_Comm_size(comm, &commSize);
        return AllocMPIJobsWorkerWise<IndexT>(jobBegin, jobEnd,
                                              commSize, commRank);
    }
}

template<std::integral IndexT>
IntegralIndexRange<IndexT> AllocMPIJobsWorkerWise(std::pair<IndexT, IndexT> jobBeginEnd, MPI_Comm comm) {
    return AllocMPIJobsWorkerWise<IndexT>(jobBeginEnd.first, jobBeginEnd.second, comm);
}

template<std::integral IndexT>
IntegralIndexRange<IndexT> AllocMPIJobsWorkerWise(std::pair<IndexT, IndexT> jobBeginEnd, int commSize, int commRank) {
    return AllocMPIJobsWorkerWise<IndexT>(jobBeginEnd.first, jobBeginEnd.second, commSize, commRank);
}

} // namespace MACE::Utility::MPIUtil
