#include "MACE/SimMACE/Hit/EMCalHit.hxx"

namespace MACE::SimMACE::Hit {

ObserverPtr<G4Allocator<EMCalHit>> EMCalHit::fgEMCalHitAllocator = nullptr;

} // namespace MACE::SimMACE::Hit
