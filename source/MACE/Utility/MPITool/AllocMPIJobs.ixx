namespace MACE::Utility::MPITool {

template<std::integral Index_t>
DividedIndexRange<Index_t> AllocMPIJobsJobWise(Index_t jobBegin, Index_t jobEnd, MPI_Comm comm) {
    return DivideIndexRangeIndexWise<Index_t>(jobBegin, jobEnd, MPICommSize(comm))[MPICommRank(comm)];
}

template<std::integral Index_t>
DividedIndexRange<Index_t> AllocMPIJobsJobWise(Index_t jobBegin, Index_t jobEnd, int commSize, int commRank) {
    return DivideIndexRangeIndexWise<Index_t>(jobBegin, jobEnd, commSize)[commRank];
}

template<std::integral Index_t>
DividedIndexRange<Index_t> AllocMPIJobsJobWise(std::pair<Index_t, Index_t> jobBeginEnd, MPI_Comm comm) {
    return AllocMPIJobsJobWise<Index_t>(jobBeginEnd.first, jobBeginEnd.second, comm);
}

template<std::integral Index_t>
DividedIndexRange<Index_t> AllocMPIJobsJobWise(std::pair<Index_t, Index_t> jobBeginEnd, int commSize, int commRank) {
    return AllocMPIJobsJobWise<Index_t>(jobBeginEnd.first, jobBeginEnd.second, commSize, commRank);
}

template<std::integral Index_t>
DividedIndexRange<Index_t> AllocMPIJobsWorkerWise(Index_t jobBegin, Index_t jobEnd, MPI_Comm comm) {
    return DivideIndexRangeTakerWise<Index_t>(jobBegin, jobEnd, MPICommSize(comm))[MPICommRank(comm)];
}

template<std::integral Index_t>
DividedIndexRange<Index_t> AllocMPIJobsWorkerWise(Index_t jobBegin, Index_t jobEnd, int commSize, int commRank) {
    return DivideIndexRangeTakerWise<Index_t>(jobBegin, jobEnd, commSize)[commRank];
}

template<std::integral Index_t>
DividedIndexRange<Index_t> AllocMPIJobsWorkerWise(std::pair<Index_t, Index_t> jobBeginEnd, MPI_Comm comm) {
    return AllocMPIJobsWorkerWise<Index_t>(jobBeginEnd.first, jobBeginEnd.second, comm);
}

template<std::integral Index_t>
DividedIndexRange<Index_t> AllocMPIJobsWorkerWise(std::pair<Index_t, Index_t> jobBeginEnd, int commSize, int commRank) {
    return AllocMPIJobsWorkerWise<Index_t>(jobBeginEnd.first, jobBeginEnd.second, commSize, commRank);
}

} // namespace MACE::Utility::MPITool
