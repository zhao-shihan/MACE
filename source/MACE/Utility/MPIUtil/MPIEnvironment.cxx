#include "MACE/Utility/MPIUtil/MPIEnvironment.hxx"

#include "mpi.h"

#include <stdexcept>

namespace MACE::Utility::MPIUtil {

ObserverPtr<MPIEnvironment> MPIEnvironment::fgInstance = nullptr;

MPIEnvironment::MPIEnvironment(int& argc, char**& argv) :
    fWorldCommRank(-1),
    fWorldCommSize(-1),
    fProcessorName() {
    // Confirm MPI condition
    int mpiInitialized;
    MPI_Initialized(&mpiInitialized);
    if (mpiInitialized) {
        throw std::logic_error("MACE::Utility::MPIUtil::MPIEnvironment: MPI environment should only be initialized once.");
    }
    // Initialize MPI
    MPI_Init(&argc, &argv);
    // Initialize fWorldCommRank
    MPI_Comm_rank(MPI_COMM_WORLD, &fWorldCommRank);
    // Initialize fWorldCommSize
    MPI_Comm_size(MPI_COMM_WORLD, &fWorldCommSize);
    // Initialize fProcessorName
    char processorName[MPI_MAX_PROCESSOR_NAME];
    int processorNameLength;
    MPI_Get_processor_name(processorName, &processorNameLength);
    fProcessorName.assign(processorName, processorNameLength);
    fProcessorName.shrink_to_fit();
    // Export the instance
    fgInstance = this;
}

MPIEnvironment::~MPIEnvironment() {
    // Finalize MPI
    MPI_Finalize();
    // Reset instance pointer
    fgInstance = nullptr;
}

}; // namespace MACE::Utility::MPIUtil
