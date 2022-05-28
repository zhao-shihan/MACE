#include "MACE/Utility/MPIUtil/CommonMPIWrapper.hxx"
#include "MACE/Utility/MPIUtil/MPIRandomUtil.hxx"

#include "CLHEP/Random/RandomEngine.h"

#include <numeric>
#include <set>
#include <vector>

namespace MACE::Utility::MPIUtil {

void MPIReSeedCLHEPRandom(CLHEP::HepRandomEngine* randEng) {
    const auto commSize = MPICommSize(MPI_COMM_WORLD);
    if (commSize == 1) { return; }
    const auto commRank = MPICommRank(MPI_COMM_WORLD);

    std::vector<long> seedSend;
    long seedRecv = 0;

    if (commRank == 0) {
        std::set<long> uniqueSeeds;
        static const auto seedMaxLD = std::nextafter((long double)std::numeric_limits<long>::max(), -1.0L);
        do {
            long newSeed;
            do {
                newSeed = seedMaxLD * std::nextafter((long double)randEng->flat(), -1.0L) - uniqueSeeds.size();
            } while (newSeed <= 0);
            uniqueSeeds.emplace(newSeed);
        } while (uniqueSeeds.size() < (size_t)commSize);

        seedSend.reserve(commSize);
        for (auto&& seed : std::as_const(uniqueSeeds)) {
            seedSend.emplace_back(seed);
        }
    }

    MPI_Scatter(seedSend.data(), 1, MPI_LONG, &seedRecv, 1, MPI_LONG, 0, MPI_COMM_WORLD);
    randEng->setSeed(seedRecv, 3);
}

} // namespace MACE::Utility::MPIUtil
