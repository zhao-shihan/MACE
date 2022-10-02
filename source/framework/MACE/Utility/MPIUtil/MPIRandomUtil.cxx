#include "MACE/Env/MPIEnv.hxx"
#include "MACE/Utility/MPIUtil/CheckedMPICall.hxx"
#include "MACE/Utility/MPIUtil/MPIRandomUtil.hxx"

#include "CLHEP/Random/RandomEngine.h"

#include "mpi.h"

#include <numeric>
#include <set>
#include <vector>

namespace MACE::Utility::MPIUtil {

void MPIReSeedCLHEPRandom(gsl::not_null<CLHEP::HepRandomEngine*> randEng) {
    const auto& mpiEnv = Env::MPIEnv::Instance();

    if (mpiEnv.Sequential()) { return; }

    std::vector<long> seedSend;
    long seedRecv = 0;

    if (mpiEnv.AtWorldMaster()) {
        static const auto seedMaxLD = std::nextafter(
            static_cast<long double>(std::numeric_limits<long>::max()), -1.0L);
        const std::size_t worldSize = mpiEnv.WorldCommSize();
        std::set<long> uniqueSeeds;
        do {
            long newSeed;
            do {
                newSeed = seedMaxLD *
                              std::nextafter(static_cast<long double>(randEng->flat()), -1.0L) -
                          uniqueSeeds.size();
            } while (newSeed <= 0);
            uniqueSeeds.emplace(newSeed);
        } while (uniqueSeeds.size() < worldSize);

        seedSend.reserve(worldSize);
        for (auto&& seed : std::as_const(uniqueSeeds)) {
            seedSend.emplace_back(seed);
        }
    }

    MACE_CHECKED_MPI_CALL(MPI_Scatter,
                          seedSend.data(),
                          1,
                          MPI_LONG,
                          &seedRecv,
                          1,
                          MPI_LONG,
                          0,
                          MPI_COMM_WORLD)
    randEng->setSeed(seedRecv, 3);
}

} // namespace MACE::Utility::MPIUtil
