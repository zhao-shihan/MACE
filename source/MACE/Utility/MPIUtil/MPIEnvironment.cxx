#include "MACE/Utility/MPIUtil/MPIEnvironment.hxx"

#include "mpi.h"

#include <stdexcept>

namespace MACE::Utility::MPIUtil {

ObserverPtr<MPIEnvironment> MPIEnvironment::fgInstance = nullptr;

MPIEnvironment::MPIEnvironment(int argc, char* argv[]) :
    fWorldCommRank(-1),
    fWorldCommSize(-1) {

    int mpiInitialized;
    MPI_Initialized(&mpiInitialized);
    if (mpiInitialized) {
        throw std::logic_error("MACE::Utility::MPIUtil::MPIEnvironment: MPI environment should only be initialized once.");
    }

    fgInstance = this;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &fWorldCommRank);
    MPI_Comm_size(MPI_COMM_WORLD, &fWorldCommRank);
}

MPIEnvironment::~MPIEnvironment() {
    MPI_Finalize();
    fgInstance = nullptr;
}

}; // namespace MACE::Utility::MPIUtil
