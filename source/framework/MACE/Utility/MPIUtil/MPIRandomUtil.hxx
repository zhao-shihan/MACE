#pragma once

#include "gsl/gsl"

namespace CLHEP {

class HepRandomEngine;

} // namespace CLHEP

namespace MACE::inline Utility::MPIUtil {

void MPIReSeedCLHEPRandom(gsl::not_null<CLHEP::HepRandomEngine*> randEng);

} // namespace MACE::inline Utility::MPIUtil
