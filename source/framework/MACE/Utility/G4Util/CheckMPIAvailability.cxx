#include "MACE/Environment/MPIEnvironment.hxx"
#include "MACE/Utility/G4Util/CheckMPIAvailability.hxx"

#include "G4Exception.hh"

namespace MACE::Utility::G4Util {

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
