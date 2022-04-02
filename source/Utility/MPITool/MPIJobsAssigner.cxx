#include "Utility/MPITool/MPIJobsAssigner.hxx"

#include <vector>

namespace MACE::Utility::MPITool {

MPIJobsAssigner::MPIJobsAssigner(int_fast64_t jobsBeginIndex, int_fast64_t jobsEndIndex, const MPI::Comm& comm) :
    fJobsIndexRange(0, 0) {
    if (MPI::Is_initialized()) {
        const auto commRank = comm.Get_rank();
        const auto commSize = comm.Get_size();

        const auto totalJobSize = jobsEndIndex - jobsBeginIndex;
        const auto basicJobSize = totalJobSize / commSize;
        const auto jobResidue = totalJobSize - basicJobSize * commSize;

        std::vector<int_fast64_t> jobSizeList(commSize, basicJobSize);
        for (long i = 0; i < jobResidue; ++i) { ++jobSizeList[i]; }

        for (int i = 0; i < commRank; ++i) { fJobsIndexRange.first += jobSizeList[i]; }
        fJobsIndexRange.second = fJobsIndexRange.first + jobSizeList[commRank];
    } else {
        fJobsIndexRange = std::make_pair(jobsBeginIndex, jobsEndIndex);
    }
}

MPIJobsAssigner::MPIJobsAssigner(const std::pair<int_fast64_t, int_fast64_t> jobsIndexRange, const MPI::Comm& comm) :
    MPIJobsAssigner(jobsIndexRange.first, jobsIndexRange.second, comm) {}

} // namespace MACE::Utility::MPITool
