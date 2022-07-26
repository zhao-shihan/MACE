#pragma once

#include <stdexcept>
#include <string>

#define MACE_CHECKED_MPI_CALL(MPI_Func, ...)                                   \
    if (const auto mpiCallErrorCode = MPI_Func(__VA_ARGS__);                   \
        mpiCallErrorCode != MPI_SUCCESS) {                                     \
        throw std::runtime_error(std::string(__FILE__)                         \
                                     .append(":")                              \
                                     .append(std::to_string(__LINE__))         \
                                     .append(": Error calling ")               \
                                     .append(#MPI_Func)                        \
                                     .append(" (error code: ")                 \
                                     .append(std::to_string(mpiCallErrorCode)) \
                                     .append(")"));                            \
    }
