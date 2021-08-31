#include "detector/hit/CalorimeterHit.hh"

using namespace MACE::SimG4::Hit;

G4Allocator<CalorimeterHit>* MACE::SimG4::Hit::CalorimeterHitAllocator = nullptr;

CalorimeterHit::CalorimeterHit(G4int trackID, G4double hitTime, G4double energy) :
    G4VHit(),
    TrackID(trackID),
    HitTime(hitTime),
    Energy(energy) {}

CalorimeterHit::~CalorimeterHit() {}

void CalorimeterHit::Draw() {}

void CalorimeterHit::Print() {}
