#include "MACE/Simulation/SimMACE/Hit/EMCalHit.hxx"

namespace MACE::Simulation::SimMACE::Hit {

ObserverPtr<G4Allocator<EMCalHit>> EMCalHit::fgEMCalHitAllocator = nullptr;

} // namespace MACE::Simulation::SimMACE::Hit
