#include "MACE/Utility/MPIUtil/CommonMPIWrapper.hxx"

namespace MACE::Utility::MPIUtil {

int MPICommRank(MPI_Comm comm) {
    int commRank;
    MPI_Comm_rank(comm, &commRank);
    return commRank;
}

int MPICommSize(MPI_Comm comm) {
    int commSize;
    MPI_Comm_size(comm, &commSize);
    return commSize;
}

bool MPIInitialized() {
    int initialized;
    MPI_Initialized(&initialized);
    return initialized;
}

bool MPIFinalized() {
    int finalized;
    MPI_Finalized(&finalized);
    return finalized;
}

std::string MPIGetProcessorNameString() {
    const auto [processorName, nameLength] = MPIGetProcessorName<MPI_MAX_PROCESSOR_NAME>();
    return std::string(processorName.data(), nameLength);
}

} // namespace MACE::Utility::MPIUtil
