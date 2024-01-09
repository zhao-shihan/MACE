#pragma once

namespace CLHEP {
class HepRandomEngine;
} // namespace CLHEP
class TRandom;

namespace MACE::inline Utility {

auto MPIReseedRandomEngine(CLHEP::HepRandomEngine* clhepRng = {}, TRandom* tRandom = {}) -> void;

} // namespace MACE::inline Utility
