#include "MACE/Simulation/SimMACE/Hit/EMCalHit.hxx"

using MACE::Simulation::SimMACE::Hit::EMCalHit;
using MACE::Utility::ObserverPtr;

ObserverPtr<G4Allocator<EMCalHit>> EMCalHit::fgEMCalHitAllocator = nullptr;
