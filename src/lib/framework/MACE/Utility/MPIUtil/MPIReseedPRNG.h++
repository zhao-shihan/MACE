#pragma once

namespace CLHEP {

class HepRandomEngine;

} // namespace CLHEP

namespace MACE::inline Utility::MPIUtil {

auto MPIReseedPRNG(CLHEP::HepRandomEngine& randEng) -> void;

} // namespace MACE::inline Utility::MPIUtil
