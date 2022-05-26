#pragma once

#include "mpi.h"

#include <array>
#include <string>
#include <utility>

namespace MACE::Utility::MPIUtil {

// These are some simple but convenient wrappers of corresponding MPI_C functions that returns values via pointer parameters,
// a little bit like the MPI C++ binding which has been removed in MPI2.2 for the reason "not very C++".
// But we wrapper them here again because we try best not to use the removed feature
// (though they are still available in most of implementations if switched on in compilation),
// and they are really useful.
// Feel free to extend them anytime when needed.

int MPICommRank(MPI_Comm comm);
int MPICommSize(MPI_Comm comm);
bool MPIInitialized();
bool MPIFinalized();
template<size_t MaxLength_v = MPI_MAX_PROCESSOR_NAME>
std::pair<std::array<char, MaxLength_v>, int> MPIGetProcessorName();
template<size_t MaxLength_v = MPI_MAX_PROCESSOR_NAME>
std::string MPIGetProcessorNameString();

} // namespace MACE::Utility::MPIUtil

#include "MACE/Utility/MPIUtil/CommonMPIWrapper.ixx"
