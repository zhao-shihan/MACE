#pragma once

#include <concepts>
#include <type_traits>
#include <vector>

namespace MACE::Utility {

template<std::integral Job_t, std::integral Worker_t>
std::vector<Job_t> AllocJobs(Job_t nJobs, Worker_t nWorkers);

} // namespace MACE::Utility

#include "MACE/Utility/AllocJobs.ixx"
