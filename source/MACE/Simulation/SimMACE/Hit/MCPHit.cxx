#include "MACE/Simulation/SimMACE/Hit/MCPHit.hxx"

using MACE::Simulation::SimMACE::Hit::MCPHit;
using MACE::Utility::ObserverPtr;

ObserverPtr<G4Allocator<MCPHit>> MCPHit::fgMCPAllocator = nullptr;
