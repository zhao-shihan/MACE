namespace MACE::Utility::MPIUtil {

template<std::integral IndexT>
DividedIndexRange<IndexT> AllocMPIJobsJobWise(IndexT jobBegin, IndexT jobEnd, MPI_Comm comm) {
    return DivideIndexRangeIndexWise<IndexT>(jobBegin, jobEnd, MPICommSize(comm))[MPICommRank(comm)];
}

template<std::integral IndexT>
DividedIndexRange<IndexT> AllocMPIJobsJobWise(IndexT jobBegin, IndexT jobEnd, int commSize, int commRank) {
    return DivideIndexRangeIndexWise<IndexT>(jobBegin, jobEnd, commSize)[commRank];
}

template<std::integral IndexT>
DividedIndexRange<IndexT> AllocMPIJobsJobWise(std::pair<IndexT, IndexT> jobBeginEnd, MPI_Comm comm) {
    return AllocMPIJobsJobWise<IndexT>(jobBeginEnd.first, jobBeginEnd.second, comm);
}

template<std::integral IndexT>
DividedIndexRange<IndexT> AllocMPIJobsJobWise(std::pair<IndexT, IndexT> jobBeginEnd, int commSize, int commRank) {
    return AllocMPIJobsJobWise<IndexT>(jobBeginEnd.first, jobBeginEnd.second, commSize, commRank);
}

template<std::integral IndexT>
DividedIndexRange<IndexT> AllocMPIJobsWorkerWise(IndexT jobBegin, IndexT jobEnd, MPI_Comm comm) {
    return DivideIndexRangeTakerWise<IndexT>(jobBegin, jobEnd, MPICommSize(comm))[MPICommRank(comm)];
}

template<std::integral IndexT>
DividedIndexRange<IndexT> AllocMPIJobsWorkerWise(IndexT jobBegin, IndexT jobEnd, int commSize, int commRank) {
    return DivideIndexRangeTakerWise<IndexT>(jobBegin, jobEnd, commSize)[commRank];
}

template<std::integral IndexT>
DividedIndexRange<IndexT> AllocMPIJobsWorkerWise(std::pair<IndexT, IndexT> jobBeginEnd, MPI_Comm comm) {
    return AllocMPIJobsWorkerWise<IndexT>(jobBeginEnd.first, jobBeginEnd.second, comm);
}

template<std::integral IndexT>
DividedIndexRange<IndexT> AllocMPIJobsWorkerWise(std::pair<IndexT, IndexT> jobBeginEnd, int commSize, int commRank) {
    return AllocMPIJobsWorkerWise<IndexT>(jobBeginEnd.first, jobBeginEnd.second, commSize, commRank);
}

} // namespace MACE::Utility::MPIUtil
