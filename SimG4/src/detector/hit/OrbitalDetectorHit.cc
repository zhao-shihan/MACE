#include "detector/hit/OrbitalDetectorHit.hh"

using namespace MACE::SimG4::Hit;

G4Allocator<OrbitalDetectorHit>* MACE::SimG4::Hit::OrbitalDetectorHitAllocator = nullptr;

OrbitalDetectorHit::OrbitalDetectorHit(G4int trackID, G4double vertexTime, const G4ThreeVector& vertexPosition, G4double hitTime, const G4ThreeVector& hitPosition, const G4ParticleDefinition* particle) :
    G4VHit(),
    TrackID(trackID),
    VertexTime(vertexTime),
    VertexPosition(vertexPosition),
    HitTime(hitTime),
    HitPosition(hitPosition),
    ParticleDefinition(particle) {}

// OrbitalDetectorHit::~OrbitalDetectorHit() {}

// void OrbitalDetectorHit::Draw() {}

// void OrbitalDetectorHit::Print() {}
