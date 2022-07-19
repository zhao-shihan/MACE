#include "MACE/Environment/MPIEnvironment.hxx"
#include "MACE/Utility/UtilMPI/MPIRandomUtil.hxx"

#include "CLHEP/Random/RandomEngine.h"

#include "mpi.h"

#include <numeric>
#include <set>
#include <vector>

namespace MACE::Utility::UtilMPI {

void MPIReSeedCLHEPRandom(CLHEP::HepRandomEngine* randEng) {
    using MACE::Environment::MPIEnvironment;

    if (MPIEnvironment::IsSerialized()) { return; }

    std::vector<long> seedSend;
    long seedRecv = 0;

    if (MPIEnvironment::IsWorldMaster()) {
        const size_t commSize = MPIEnvironment::WorldCommSize();

        std::set<long> uniqueSeeds;
        static const auto seedMaxLD = std::nextafter((long double)std::numeric_limits<long>::max(), -1.0L);
        do {
            long newSeed;
            do {
                newSeed = seedMaxLD * std::nextafter((long double)randEng->flat(), -1.0L) - uniqueSeeds.size();
            } while (newSeed <= 0);
            uniqueSeeds.emplace(newSeed);
        } while (uniqueSeeds.size() < commSize);

        seedSend.reserve(commSize);
        for (auto&& seed : std::as_const(uniqueSeeds)) {
            seedSend.emplace_back(seed);
        }
    }

    MPI_Scatter(seedSend.data(), 1, MPI_LONG, &seedRecv, 1, MPI_LONG, 0, MPI_COMM_WORLD);
    randEng->setSeed(seedRecv, 3);
}

} // namespace MACE::Utility::UtilMPI
