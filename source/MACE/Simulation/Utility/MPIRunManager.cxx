#include "MACE/Simulation/Utility/CheckMPIAvailability.hxx"
#include "MACE/Simulation/Utility/MPIRunManager.hxx"
#include "MACE/Utility/AllocJobs.hxx"

#include "G4Exception.hh"
#include "Randomize.hh"

#include "mpi.h"

#include <set>

namespace MACE::Simulation::Utility {

MPIRunManager::MPIRunManager() :
    fCommRank(ConstructorGetMPICommRank()),
    fCommSize(ConstructorGetMPICommSize()) {}

void MPIRunManager::BeamOn(G4int nEvent, const char* macroFile, G4int nSelect) {
    CheckMPIAvailability();
    if (CheckNEventIsAtLeastCommSize(nEvent)) {
        DistributeSeed();
        G4RunManager::BeamOn(DistributeEvent(nEvent), macroFile, nSelect);
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
    }
    return true;
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

G4int MPIRunManager::DistributeEvent(G4int nEvent) const {
    if (fCommSize == 1) { return nEvent; }
    const auto nEventList = MACE::Utility::AllocJobs<G4int, int>(nEvent, fCommSize);
    return nEventList[fCommRank];
}

int MPIRunManager::ConstructorGetMPICommRank() {
    CheckMPIAvailability();
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    return rank;
}

int MPIRunManager::ConstructorGetMPICommSize() {
    CheckMPIAvailability();
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    return size;
}

} // namespace MACE::Simulation::Utility
