#pragma once

#include "gsl/gsl"

namespace CLHEP {

class HepRandomEngine;

} // namespace CLHEP

namespace MACE::Utility::MPIUtil {

void MPIReSeedCLHEPRandom(gsl::not_null<CLHEP::HepRandomEngine*> randEng);

} // namespace MACE::Utility::MPIUtil
