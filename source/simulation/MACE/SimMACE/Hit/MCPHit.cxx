#include "MACE/SimMACE/Hit/MCPHit.hxx"

namespace MACE::SimMACE::Hit {

ObserverPtr<G4Allocator<MCPHit>> MCPHit::fgMCPHitAllocator = nullptr;

} // namespace MACE::SimMACE::Hit
