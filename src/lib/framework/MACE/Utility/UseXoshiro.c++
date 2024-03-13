#include "MACE/Extension/CLHEPX/Random/Xoshiro.h++"
#include "MACE/Extension/ROOTX/Math/Xoshiro.h++"
#include "MACE/Extension/stdx/arraynx.h++"
#include "MACE/Math/Random/Generator/SplitMix64.h++"
#include "MACE/Utility/UseXoshiro.h++"

#include "CLHEP/Random/Random.h"

#include "TRandom.h"

#include <memory>

namespace MACE::inline Utility {

#define MACE_UTILITY_USE_XOSHIRO_DEFINITION(NBit)                                                   \
    template<>                                                                                      \
    [[nodiscard]] auto UseXoshiro<NBit>() -> std::any {                                             \
        struct Xoshiro##NBit {                                                                      \
            CLHEPX::Random::Xoshiro##NBit##SS clhep;                                                \
            ROOTX::Math::Xoshiro##NBit##PP root;                                                    \
        };                                                                                          \
        /* New random engines */                                                                    \
        auto xoshiro{std::make_shared<Xoshiro##NBit>()}; /* use copyable shared_ptr for std::any */ \
        /* Set random engines */                                                                    \
        CLHEP::HepRandom::setTheEngine(&xoshiro->clhep);                                            \
        delete gRandom, gRandom = &xoshiro->root;                                                   \
        /* Try to decorrelate Xoshiro++ with Xoshiro** */                                           \
        gRandom->SetSeed(Math::Random::SplitMix64{std::bit_cast<std::uint64_t>(                     \
            stdx::array2u32{gRandom->Integer(-1) + 1, gRandom->Integer(-1) + 1})}());               \
        return xoshiro;                                                                             \
    }

MACE_UTILITY_USE_XOSHIRO_DEFINITION(256)
MACE_UTILITY_USE_XOSHIRO_DEFINITION(512)

#undef MACE_UTILITY_USE_XOSHIRO_DEFINITION

} // namespace MACE::inline Utility
