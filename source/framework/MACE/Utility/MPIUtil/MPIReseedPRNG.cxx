#include "MACE/Env/MPIEnv.hxx"
#include "MACE/Math/Random/Distribution/Uniform.hxx"
#include "MACE/Math/Random/Generator/Xoshiro256PP.hxx"
#include "MACE/Utility/MPIUtil/MPICallWithCheck.hxx"
#include "MACE/Utility/MPIUtil/MPIReseedPRNG.hxx"

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
        static_assert(std::same_as<std::uint64_t, Math::Random::Xoshiro256PP::ResultType>);

        std::array<unsigned int, sizeof(std::uint64_t) / sizeof(unsigned int)> xoshiro256PPSeed;
        std::ranges::generate(xoshiro256PPSeed, [&] { return randEng.operator unsigned int(); });
        Math::Random::Xoshiro256PP xoshiro256PP(std::bit_cast<std::uint64_t>(xoshiro256PPSeed));

        std::set<long> uniqueSeeds;
        Math::Random::Uniform<long> uniformLong(1, std::numeric_limits<long>::max() - 1);
        do {
            uniqueSeeds.emplace(uniformLong(xoshiro256PP));
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
