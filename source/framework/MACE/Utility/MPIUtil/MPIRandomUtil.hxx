#pragma once

namespace CLHEP {
class HepRandomEngine;
} // namespace CLHEP

namespace MACE::Utility::MPIUtil {

void MPIReSeedCLHEPRandom(CLHEP::HepRandomEngine* randEng);

} // namespace MACE::Utility::MPIUtil
