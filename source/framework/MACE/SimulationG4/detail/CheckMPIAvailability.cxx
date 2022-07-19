#include "MACE/Environment/MPIEnvironment.hxx"
#include "MACE/SimulationG4/detail/CheckMPIAvailability.hxx"

#include "G4Exception.hh"

namespace MACE::SimulationG4::Detail {

void CheckMPIAvailability() {
    using MACE::Environment::MPIEnvironment;
    if (not MPIEnvironment::Available()) {
        G4Exception("MACE::Utility::G4Util::MPIRunManager::CheckMPI()",
                    "MPINotAvailable",
                    FatalException,
                    "MPI must be initialized and not finalized."
                    "(This should be an unusual execption. Please contact developers.)");
    }
}

} // namespace MACE::Utility::G4Util
