#pragma once

#include "mpi.h"

#include <utility>

namespace MACE::Utility::MPITool {

class MPIJobsAssigner final {
public:
    MPIJobsAssigner(int_fast64_t jobsBeginIndex, int_fast64_t jobsEndIndex, const MPI::Comm& comm = MPI::COMM_WORLD);
    MPIJobsAssigner(const std::pair<int_fast64_t, int_fast64_t> jobsIndexRange, const MPI::Comm& comm = MPI::COMM_WORLD);
    ~MPIJobsAssigner() noexcept = default;
    MPIJobsAssigner(const MPIJobsAssigner&) = delete;
    MPIJobsAssigner& operator=(const MPIJobsAssigner&) = delete;

    const auto& GetJobsIndexRange() const { return fJobsIndexRange; }

private:
    std::pair<int_fast64_t, int_fast64_t> fJobsIndexRange;
};

} // namespace MACE::Utility::MPITool
