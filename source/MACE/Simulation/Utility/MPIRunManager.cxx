#include "MACE/Simulation/Utility/CheckMPIAvailability.hxx"
#include "MACE/Simulation/Utility/MPIRunManager.hxx"
#include "MACE/Utility/MPIUtil/AllocMPIJobs.hxx"
#include "MACE/Utility/MPIUtil/CommonMPIWrapper.hxx"
#include "MACE/Utility/MPIUtil/MPIRandomUtil.hxx"

#include "G4Exception.hh"
#include "Randomize.hh"

#include "mpi.h"

#include <set>

namespace MACE::Simulation::Utility {

using namespace MACE::Utility::MPIUtil;

MPIRunManager::MPIRunManager() :
    fCommRank((CheckMPIAvailability(), MPICommRank(MPI_COMM_WORLD))),
    fCommSize(MPICommSize(MPI_COMM_WORLD)),
    fTotalNumberOfEventsToBeProcessed(0),
    fEventIDRange() {}

void MPIRunManager::BeamOn(G4int nEvent, const char* macroFile, G4int nSelect) {
    CheckMPIAvailability();
    if (CheckNEventIsAtLeastCommSize(nEvent)) {
        MPIReSeedCLHEPRandom(G4Random::getTheEngine());
        fTotalNumberOfEventsToBeProcessed = nEvent;
        fEventIDRange = AllocMPIJobsJobWise(0, nEvent, fCommSize, fCommRank);
        G4RunManager::BeamOn(fEventIDRange.count, macroFile, nSelect);
    }
}

G4bool MPIRunManager::CheckNEventIsAtLeastCommSize(G4int nEvent) const {
    if (nEvent < fCommSize) {
        G4Exception("MACE::Simulation::Utility::MPIRunManager::CheckNEventIsAtLeastCommSize(...)",
                    "TooFewNEventOrTooMuchRank",
                    JustWarning,
                    "The number of G4Event must be greater or equal to the number of MPI ranks,\n"
                    "otherwise deadlock could raise in execution code.\n"
                    "Please be careful.");
        return false;
    } else {
        return true;
    }
}

} // namespace MACE::Simulation::Utility
