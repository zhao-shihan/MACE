#include "MACE/Simulation/Utility/CheckMPIAvailability.hxx"

#include "G4Exception.hh"

#include "mpi.h"

namespace MACE::Simulation::Utility {

void CheckMPIAvailability() {
    int initialized;
    MPI_Initialized(&initialized);
    int finalized;
    MPI_Finalized(&finalized);
    if (not initialized or finalized) {
        G4Exception("MACE::Simulation::Utility::MPIRunManager::CheckMPI()",
                    "MPINotAvailable",
                    FatalException,
                    "MPI must be initialized and not finalized."
                    "(This should be an unusual execption. Please contact developers.)");
    }
}

} // namespace MACE::Simulation::Utility
