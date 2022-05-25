#pragma once

namespace CLHEP {
class HepRandomEngine;
} // namespace CLHEP

namespace MACE::Utility::MPITool {

void MPIReSeedCLHEPRandom(CLHEP::HepRandomEngine* randEng);

} // namespace MACE::Utility::MPITool
