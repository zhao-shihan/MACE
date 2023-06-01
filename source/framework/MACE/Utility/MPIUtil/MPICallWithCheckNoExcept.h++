#pragma once

#include <iostream>

#define MACE_MPI_CALL_WITH_CHECK_NOEXCEPT(MPI_Function, ...)                              \
    if (const auto mpiCallErrorCode = MPI_Function(__VA_ARGS__);                          \
        mpiCallErrorCode != MPI_SUCCESS) [[unlikely]] {                                   \
        std::cerr << "Fatal error: " << __FILE__ << ':' << __LINE__ << ": Error calling " \
                  << #MPI_Function << " (error code: " << mpiCallErrorCode << ')'         \
                  << std::endl;                                                           \
    }
