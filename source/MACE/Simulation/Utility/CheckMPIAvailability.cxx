#include "MACE/Simulation/Utility/CheckMPIAvailability.hxx"
#include "MACE/Utility/MPITool/CommonMPIWrapper.hxx"

#include "G4Exception.hh"

#include "mpi.h"

namespace MACE::Simulation::Utility {

using namespace MACE::Utility::MPITool;

void CheckMPIAvailability() {
    if (not MPIInitialized() or MPIFinalized()) {
        G4Exception("MACE::Simulation::Utility::MPIRunManager::CheckMPI()",
                    "MPINotAvailable",
                    FatalException,
                    "MPI must be initialized and not finalized."
                    "(This should be an unusual execption. Please contact developers.)");
    }
}

} // namespace MACE::Simulation::Utility
