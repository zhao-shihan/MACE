#pragma once

#include <iostream>
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

#define MACE_CHECKED_MPI_CALL_NOEXCEPT(MPI_Func, ...)                                                                                                         \
    if (const auto mpiCallErrorCode = MPI_Func(__VA_ARGS__);                                                                                                  \
        mpiCallErrorCode != MPI_SUCCESS) {                                                                                                                    \
        std::cerr << "Fatal: " << __FILE__ << ':' << __LINE__ << ": Error calling " << #MPI_Func << " (error code: " << mpiCallErrorCode << ')' << std::endl; \
        std::abort();                                                                                                                                         \
    }
