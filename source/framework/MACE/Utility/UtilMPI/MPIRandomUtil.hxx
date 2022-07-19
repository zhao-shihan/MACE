#pragma once

namespace CLHEP {
class HepRandomEngine;
} // namespace CLHEP

namespace MACE::Utility::UtilMPI {

void MPIReSeedCLHEPRandom(CLHEP::HepRandomEngine* randEng);

} // namespace MACE::Utility::MPIUtil
