#pragma once

namespace CLHEP {

class HepRandomEngine;

} // namespace CLHEP

namespace MACE::inline Utility::MPIUtil {

void MPIReseedPRNG(CLHEP::HepRandomEngine& randEng);

} // namespace MACE::inline Utility::MPIUtil
