#include "Simulation/SimMACE/Hit/VertexDetectorHit.hxx"

using MACE::Simulation::SimMACE::Hit::VertexDetectorHit;
using MACE::Utility::ObserverPtr;

ObserverPtr<G4Allocator<VertexDetectorHit>> VertexDetectorHit::fgVertexDetectorAllocator = nullptr;
