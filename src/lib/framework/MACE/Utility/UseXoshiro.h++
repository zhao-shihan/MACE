#pragma once

#include <any>

namespace MACE::inline Utility {

/// @brief Use Xoshiro random engine for CLHEP and ROOT. Xoshiro** for CLHEP and Xoshiro++ for ROOT.
/// @tparam Xoshiro bit width.
/// @return An internal object holds the Xoshiro CLHEP and ROOT random engine. DO NOT DISCARD return value.
/// @warning DO NOT DISCARD return value. Otherwise new random engines are destructed immediately.
template<unsigned ABitWidth>
[[nodiscard]] auto UseXoshiro() -> std::any;

} // namespace MACE::inline Utility
