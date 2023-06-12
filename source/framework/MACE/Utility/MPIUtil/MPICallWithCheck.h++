#pragma once

#include "fmt/format.h"

#include <stdexcept>

#define MACE_MPI_CALL_WITH_CHECK(MPI_Function, ...)                                                            \
    if (const auto mpiCallErrorCode = MPI_Function(__VA_ARGS__);                                               \
        mpiCallErrorCode != MPI_SUCCESS) {                                                                     \
        throw std::runtime_error(fmt::format(__FILE__ ":{}: Error calling " #MPI_Function " (error code: {})", \
                                             __LINE__, mpiCallErrorCode));                                     \
    }
