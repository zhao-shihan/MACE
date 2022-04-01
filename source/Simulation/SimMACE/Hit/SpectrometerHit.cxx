#include "Simulation/SimMACE/Hit/SpectrometerHit.hxx"

using MACE::Simulation::SimMACE::Hit::SpectrometerHit;
using MACE::Utility::ObserverPtr;

ObserverPtr<G4Allocator<SpectrometerHit>> SpectrometerHit::fgSpectrometerHitAllocator = nullptr;
