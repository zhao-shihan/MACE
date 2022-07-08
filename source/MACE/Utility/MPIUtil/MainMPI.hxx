#pragma once

#include "MACE/Utility/MPIUtil/MPIEnvironment.hxx"

/// @brief A user-defined, TU-local "main" of MPI program.
/// This function is not defined at anywhere else but user's code, as the replacement of the original main.
/// @note TU-local: https://en.cppreference.com/w/cpp/language/tu_local
static int main_MPI(int argc, char* argv[]);

int main(int argc, char* argv[]) {
    // MPI environment Initialization
    auto mpiEnvironment = new MACE::Utility::MPIUtil::MPIEnvironment(argc, argv);

    // Execute user's main
    auto errorCode = main_MPI(argc, argv);

    // MPI environment finalization
    delete mpiEnvironment;

    return errorCode;
}
