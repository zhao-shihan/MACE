#include "SimMACE/Hit/CalorimeterHit.hxx"

using namespace MACE::SimMACE::Hit;

MACE::ObserverPtr<G4Allocator<CalorimeterHit>> CalorimeterHit::fgCalorimeterHitAllocator = nullptr;
