#include "MACE/Simulation/Utility/MPIRunManager.hxx"
#include "MACE/Utility/AllocJobs.hxx"

#include "G4Exception.hh"
#include "G4StateManager.hh"
#include "Randomize.hh"

#include "mpi.h"

#include <set>

namespace MACE::Simulation::Utility {

MPIRunManager::MPIRunManager() :
    fCommRank(0),
    fCommSize(1) {
    CheckMPI();
    MPI_Comm_rank(MPI_COMM_WORLD, &fCommRank);
    MPI_Comm_size(MPI_COMM_WORLD, &fCommSize);
}

void MPIRunManager::BeamOn(G4int nEvent, const char* macroFile, G4int nSelect) {
    CheckMPI();
    DistributeSeed();
    G4RunManager::BeamOn(DistributeEvent(nEvent), macroFile, nSelect);
}

void MPIRunManager::DistributeSeed() const {
    if (fCommSize == 1) { return; }

    std::vector<long> seedSend;
    long seedRecv = 0;

    if (fCommRank == 0) {
        auto* const randEng = G4Random::getTheEngine();
        std::set<long> uniqueSeeds{randEng->getSeed()};

        static const long double seedMaxLD = std::nextafter((long double)std::numeric_limits<long>::max(), -1.0L);
        do {
            uniqueSeeds.emplace((long double)randEng->flat() * seedMaxLD);
        } while (uniqueSeeds.size() < (size_t)fCommSize);

        seedSend.reserve(fCommSize);
        for (auto&& seed : std::as_const(uniqueSeeds)) {
            seedSend.emplace_back(seed);
        }
    }

    MPI_Scatter(seedSend.data(), 1, MPI_LONG, &seedRecv, 1, MPI_LONG, 0, MPI_COMM_WORLD);
    G4Random::setTheSeed(seedRecv);
}

int MPIRunManager::DistributeEvent(G4int nEvent) const {
    if (fCommSize == 1) { return nEvent; }
    const auto nEventList = MACE::Utility::AllocJobs<G4int, int>(nEvent, fCommSize);
    return nEventList[fCommRank];
}

void MPIRunManager::CheckMPI() {
    int initialized;
    MPI_Initialized(&initialized);
    int finalized;
    MPI_Finalized(&finalized);
    if (not initialized or finalized) {
        G4Exception("MACE::Simulation::Utility::CheckMPI()",
                    "MPINotAvailable",
                    FatalException,
                    "MPI must be initialized and not finalized.");
    }
}

} // namespace MACE::Simulation::Utility
