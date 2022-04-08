#include "MACE/Simulation/SimMACE/Hit/CDCHit.hxx"

using MACE::Simulation::SimMACE::Hit::CDCHit;
using MACE::Utility::ObserverPtr;

ObserverPtr<G4Allocator<CDCHit>> CDCHit::fgCDCHitAllocator = nullptr;
