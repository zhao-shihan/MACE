#include "Simulation/SimMACE/Hit/CalorimeterHit.hxx"

using MACE::Simulation::SimMACE::Hit::CalorimeterHit;
using MACE::Utility::ObserverPtr;

ObserverPtr<G4Allocator<CalorimeterHit>> CalorimeterHit::fgCalorimeterHitAllocator = nullptr;
