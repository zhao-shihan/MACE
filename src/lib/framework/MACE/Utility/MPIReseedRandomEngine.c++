#include "MACE/Env/MPIEnv.h++"
#include "MACE/Env/Memory/Singleton.h++"
#include "MACE/Extension/stdx/to_unsigned.h++"
#include "MACE/Math/Random/Distribution/Uniform.h++"
#include "MACE/Math/Random/Generator/Xoshiro256PP.h++"
#include "MACE/Utility/MPIReseedRandomEngine.h++"

#include "CLHEP/Random/Random.h"

#include "TRandom.h"

#include "mpi.h"

#include "gsl/gsl"

#include <array>
#include <bit>
#include <cassert>
#include <concepts>
#include <numeric>
#include <set>
#include <type_traits>
#include <utility>

namespace MACE::inline Utility {

namespace internal {

template<std::integral T>
auto MasterMakeUniqueSeedSeries(auto xsr256Seed) -> std::set<T> {
    static_assert(std::same_as<Math::Random::Xoshiro256PP::SeedType, std::uint64_t>);
    Math::Random::Xoshiro256PP xsr256{std::bit_cast<std::uint64_t>(xsr256Seed)};
    Math::Random::Uniform<T> uniform{1, std::numeric_limits<T>::max() - 1};
    std::set<T> uniqueSeeds;
    const auto worldSize{Env::MPIEnv::Instance().CommWorldSize()};
    do {
        uniqueSeeds.emplace(uniform(xsr256));
    } while (ssize(uniqueSeeds) < worldSize);
    return uniqueSeeds;
}

} // namespace internal

auto MPIReseedRandomEngine(CLHEP::HepRandomEngine* clhepRng,
                           TRandom* tRandom) -> void {
    const auto& mpiEnv{Env::MPIEnv::Instance()};
    if (mpiEnv.Sequential()) { return; }

    if (clhepRng == nullptr) { clhepRng = CLHEP::HepRandom::getTheEngine(); }
    if (tRandom == nullptr) { tRandom = gRandom; }

    struct Seed {
        bool clhepNull{true};
        bool rootNull{true};
        long clhep{0};
        unsigned root{0};
    };
    static_assert(std::is_same_v<decltype(Seed::clhep), decltype(clhepRng->getSeed())>);
    static_assert(std::is_same_v<decltype(Seed::root), decltype(tRandom->GetSeed())>);

    MPI_Datatype structSeed;
    MPI_Type_create_struct(4,                                                 // count
                           std::array<int, 4>{1,                              // array_of_block_lengths
                                              1,                              // array_of_block_lengths
                                              1,                              // array_of_block_lengths
                                              1}                              // array_of_block_lengths
                               .data(),                                       // array_of_block_lengths
                           std::array<MPI_Aint, 4>{offsetof(Seed, clhepNull), // array_of_displacements
                                                   offsetof(Seed, rootNull),  // array_of_displacements
                                                   offsetof(Seed, clhep),     // array_of_displacements
                                                   offsetof(Seed, root)}      // array_of_displacements
                               .data(),                                       // array_of_displacements
                           std::array<MPI_Datatype, 4>{MPI_CXX_BOOL,          // array_of_types
                                                       MPI_CXX_BOOL,          // array_of_types
                                                       MPI_LONG,              // array_of_types
                                                       MPI_UNSIGNED}          // array_of_types
                               .data(),                                       // array_of_types
                           &structSeed);                                      // newtype

    std::vector<Seed> seedSend(mpiEnv.CommWorldSize());
    if (mpiEnv.OnCommWorldMaster()) {
        if (clhepRng != nullptr) {
            std::array<unsigned int, sizeof(std::uint64_t) / sizeof(unsigned int)> xsr256Seed;
            std::ranges::generate(xsr256Seed, [&] { return clhepRng->operator unsigned int(); });
            for (gsl::index i{};
                 const auto& s : internal::MasterMakeUniqueSeedSeries<decltype(Seed::clhep)>(xsr256Seed)) {
                seedSend[i].clhepNull = false;
                seedSend[i].clhep = s;
                ++i;
            }
        }
        if (tRandom != nullptr) {
            static_assert(std::same_as<decltype(tRandom->Integer(std::numeric_limits<UInt_t>::max()) + 1), UInt_t>);
            std::array<UInt_t, sizeof(std::uint64_t) / sizeof(UInt_t)> xsr256Seed;
            std::ranges::generate(xsr256Seed, [&] { return tRandom->Integer(std::numeric_limits<UInt_t>::max()) + 1; });
            for (gsl::index i{};
                 const auto& s : internal::MasterMakeUniqueSeedSeries<decltype(Seed::root)>(xsr256Seed)) {
                seedSend[i].rootNull = false;
                seedSend[i].root = s;
                ++i;
            }
        }
    }

    Seed seedRecv;
    MPI_Type_commit(&structSeed);
    MPI_Scatter(seedSend.data(), // sendbuf
                1,               // sendcount
                structSeed,      // sendtype
                &seedRecv,       // recvbuf
                1,               // recvcount
                structSeed,      // recvtype
                0,               // root
                MPI_COMM_WORLD); // comm
    MPI_Type_free(&structSeed);

    if (seedRecv.clhepNull xor (clhepRng == nullptr)) { throw std::logic_error{"CLHEP random engine null/!null inconsistent"}; }
    if (seedRecv.rootNull xor (tRandom == nullptr)) { throw std::logic_error{"ROOT random engine null/!null inconsistent"}; }
    if (clhepRng != nullptr) {
        assert(0 < seedRecv.clhep and seedRecv.clhep < std::numeric_limits<decltype(seedRecv.clhep)>::max());
        clhepRng->setSeed(seedRecv.clhep, 3);
    }
    if (tRandom != nullptr) {
        assert(0 < seedRecv.root and seedRecv.root < std::numeric_limits<decltype(seedRecv.root)>::max());
        tRandom->SetSeed(seedRecv.root);
    }
}

} // namespace MACE::inline Utility
