#include "MACE/Extension/CLHEPX/Random/Xoshiro.h++"
#include "MACE/Extension/ROOTX/Math/Xoshiro.h++"
#include "MACE/Extension/stdx/arraynx.h++"
#include "MACE/Math/Random/Generator/SplitMix64.h++"
#include "MACE/Utility/UseXoshiro.h++"

#include "CLHEP/Random/Random.h"

#include "TRandom.h"

#include <memory>

namespace MACE::inline Utility {

template<>
[[nodiscard]] auto UseXoshiro<256>() -> std::any {
    struct Xoshiro256 {
        CLHEPX::Random::Xoshiro256SS clhep;
        ROOTX::Math::Xoshiro256PP root;
    };
    // New random engines
    auto xoshiro{std::make_shared<Xoshiro256>()}; // use copyable shared_ptr for std::any
    // Set random engines
    CLHEP::HepRandom::setTheEngine(&xoshiro->clhep);
    delete gRandom, gRandom = &xoshiro->root;
    // Try to decorrelate Xoshiro++ with Xoshiro**
    gRandom->SetSeed(Math::Random::SplitMix64{std::bit_cast<std::uint64_t>(
        stdx::array2u32{gRandom->Integer(-1) + 1, gRandom->Integer(-1) + 1})}());
    return xoshiro;
}

template<>
[[nodiscard]] auto UseXoshiro<512>() -> std::any {
    struct Xoshiro512 {
        CLHEPX::Random::Xoshiro512SS clhep;
        ROOTX::Math::Xoshiro512PP root;
    };
    // New random engines
    auto xoshiro{std::make_shared<Xoshiro512>()}; // use copyable shared_ptr for std::any
    // Set random engines
    CLHEP::HepRandom::setTheEngine(&xoshiro->clhep);
    delete gRandom, gRandom = &xoshiro->root;
    // Try to decorrelate Xoshiro++ with Xoshiro**
    gRandom->SetSeed(Math::Random::SplitMix64{std::bit_cast<std::uint64_t>(
        stdx::array2u32{gRandom->Integer(-1) + 1, gRandom->Integer(-1) + 1})}());
    return xoshiro;
}

} // namespace MACE::inline Utility
