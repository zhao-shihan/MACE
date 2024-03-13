#pragma once

#include <any>

namespace MACE::inline Utility {

/// @brief Use Xoshiro random engine for CLHEP and ROOT. Xoshiro** for CLHEP and Xoshiro++ for ROOT.
/// @tparam Xoshiro bit width (256 or 512)
/// @return An internal object holds the Xoshiro CLHEP and ROOT random engine. DO NOT DISCARD return value.
/// @warning DO NOT DISCARD return value. Otherwise new random engines are destructed immediately.
template<unsigned ABitWidth>
    requires(ABitWidth == 256 or ABitWidth == 512)
[[nodiscard]] auto UseXoshiro() -> std::any;

} // namespace MACE::inline Utility
