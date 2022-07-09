#include "MACE/Utility/G4Util/CheckMPIAvailability.hxx"
#include "MACE/Utility/MPIUtil/MPIEnvironment.hxx"

#include "G4Exception.hh"

namespace MACE::Utility::G4Util {

using namespace MACE::Utility::MPIUtil;

void CheckMPIAvailability() {
    if (not MPIEnvironment::Available()) {
        G4Exception("MACE::Utility::G4Util::MPIRunManager::CheckMPI()",
                    "MPINotAvailable",
                    FatalException,
                    "MPI must be initialized and not finalized."
                    "(This should be an unusual execption. Please contact developers.)");
    }
}

} // namespace MACE::Utility::G4Util
