#include "detector/hit/CalorimeterHit.hh"

using namespace MACE::SimG4::Hit;

G4Allocator<CalorimeterHit>* MACE::SimG4::Hit::CalorimeterHitAllocator = nullptr;

CalorimeterHit::CalorimeterHit(G4int trackID, G4double hitTime, const G4ThreeVector& hitPosition) :
    G4VHit(),
    TrackID(trackID),
    HitTime(hitTime),
    HitPosition(hitPosition) {}

CalorimeterHit::~CalorimeterHit() {}

void CalorimeterHit::Draw() {}

void CalorimeterHit::Print() {}
