#include "MACE/Env/MPIEnv.h++"
#include "MACE/Math/Random/Distribution/Uniform.h++"
#include "MACE/Math/Random/Generator/Xoshiro512SS.h++"
#include "MACE/Utility/MPIUtil/MPICallWithCheck.h++"
#include "MACE/Utility/MPIUtil/MPIReseedPRNG.h++"

#include "CLHEP/Random/RandomEngine.h"

#include "mpi.h"

#include <algorithm>
#include <array>
#include <bit>
#include <concepts>
#include <numeric>
#include <set>
#include <vector>

namespace MACE::inline Utility::MPIUtil {

void MPIReseedPRNG(CLHEP::HepRandomEngine& randEng) {
    const auto& mpiEnv = Env::MPIEnv::Instance();
    if (mpiEnv.Sequential()) { return; }

    const std::size_t worldSize = mpiEnv.CommWorldSize();
    std::vector<long> seedsSend(mpiEnv.AtCommWorldMaster() ? worldSize : 0);
    if (mpiEnv.AtCommWorldMaster()) {
        static_assert(std::same_as<std::uint64_t, Math::Random::Xoshiro512SS::ResultType>);

        std::array<unsigned int, sizeof(std::uint64_t) / sizeof(unsigned int)> xoshiro512SSSeed;
        std::ranges::generate(xoshiro512SSSeed, [&] { return randEng.operator unsigned int(); });
        Math::Random::Xoshiro512SS xoshiro512SS(std::bit_cast<std::uint64_t>(xoshiro512SSSeed));

        std::set<long> uniqueSeeds;
        Math::Random::Uniform<long> uniformLong(1, std::numeric_limits<long>::max() - 1);
        do {
            uniqueSeeds.emplace(uniformLong(xoshiro512SS));
        } while (uniqueSeeds.size() < worldSize);
        std::ranges::copy(uniqueSeeds, seedsSend.begin());
    }

    long seedRecv;
    MACE_MPI_CALL_WITH_CHECK(MPI_Scatter,
                             seedsSend.data(),
                             1,
                             MPI_LONG,
                             &seedRecv,
                             1,
                             MPI_LONG,
                             0,
                             MPI_COMM_WORLD)
    randEng.setSeed(seedRecv, 3);
}

} // namespace MACE::inline Utility::MPIUtil
