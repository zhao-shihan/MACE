#pragma once

#include <cstdlib>
#include <iostream>

#define MACE_CHECKED_MPI_CALL_NOEXCEPT(MPI_Func, ...)                                                                                                         \
    if (const auto mpiCallErrorCode = MPI_Func(__VA_ARGS__);                                                                                                  \
        mpiCallErrorCode != MPI_SUCCESS) {                                                                                                                    \
        std::cerr << "Fatal: " << __FILE__ << ':' << __LINE__ << ": Error calling " << #MPI_Func << " (error code: " << mpiCallErrorCode << ')' << std::endl; \
        std::abort();                                                                                                                                         \
    }
