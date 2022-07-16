#pragma once

namespace MACE::Utility::G4Util {

/// Check the availability of MPI environment through MPIEnviroment::Available.
/// If not available, raise a G4Exception of fatal. Thus should only be used in G4 routine.
/// @attention This function should only be used in G4 routine.
void CheckMPIAvailability();

} // namespace MACE::Utility::G4Util
