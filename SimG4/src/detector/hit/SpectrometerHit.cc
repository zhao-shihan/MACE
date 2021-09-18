#include "detector/hit/SpectrometerHit.hh"

using namespace MACE::SimG4::Hit;

G4Allocator<SpectrometerHit>* MACE::SimG4::Hit::SpectrometerHitAllocator = nullptr;

SpectrometerHit::SpectrometerHit(G4int trackID, G4int chamberID, G4double vertexTime, const G4ThreeVector& vertexPosition, G4double hitTime, const G4ThreeVector& hitPosition, const G4ParticleDefinition* particle) :
    G4VHit(),
    TrackID(trackID),
    ChamberID(chamberID),
    VertexTime(vertexTime),
    VertexPosition(vertexPosition),
    HitTime(hitTime),
    HitPosition(hitPosition),
    ParticleDefinition(particle) {}

// SpectrometerHit::~SpectrometerHit() {}

// void SpectrometerHit::Draw() {}

// void SpectrometerHit::Print() {}
