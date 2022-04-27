#include "MACE/Simulation/SimMACE/Hit/MCPHit.hxx"

namespace MACE::Simulation::SimMACE::Hit {

ObserverPtr<G4Allocator<MCPHit>> MCPHit::fgMCPHitAllocator = nullptr;

} // namespace MACE::Simulation::SimMACE::Hit
