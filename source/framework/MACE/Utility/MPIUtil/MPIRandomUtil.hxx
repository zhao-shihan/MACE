#pragma once

#include "MACE/Utility/ObserverPtr.hxx"

namespace CLHEP {

class HepRandomEngine;

} // namespace CLHEP

namespace MACE::Utility::MPIUtil {

void MPIReSeedCLHEPRandom(ObserverPtr<CLHEP::HepRandomEngine> randEng);

} // namespace MACE::Utility::MPIUtil
