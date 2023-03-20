#pragma once

#include <stdexcept>
#include <string>

#define MACE_MPI_CALL_WITH_CHECK(MPI_Function, ...)                            \
    if (const auto mpiCallErrorCode = MPI_Function(__VA_ARGS__);               \
        mpiCallErrorCode != MPI_SUCCESS) {                                     \
        throw std::runtime_error(std::string(__FILE__)                         \
                                     .append(":")                              \
                                     .append(std::to_string(__LINE__))         \
                                     .append(": Error calling ")               \
                                     .append(#MPI_Function)                    \
                                     .append(" (error code: ")                 \
                                     .append(std::to_string(mpiCallErrorCode)) \
                                     .append(")"));                            \
    }
