#include "PSIMACEGammaCsIHit.hh"

#include "G4UnitsTable.hh"

G4ThreadLocal G4Allocator<PSIMACEGammaCsIHit>* PSIMACEGammaCsIHitAllocator = 0;

PSIMACEGammaCsIHit::PSIMACEGammaCsIHit() :
    time(0.),
    // particleName("undefined"),
    energy(0.) {}

PSIMACEGammaCsIHit::~PSIMACEGammaCsIHit() {}

PSIMACEGammaCsIHit::PSIMACEGammaCsIHit(const PSIMACEGammaCsIHit& right) :
    G4VHit(right) {
    time = right.time;
    // particleName = right.particleName;
    energy = right.energy;
}

const PSIMACEGammaCsIHit& PSIMACEGammaCsIHit::operator=(const PSIMACEGammaCsIHit& right) {
    if (this != &right) {
        time = right.time;
        // particleName = right.particleName;
        energy = right.energy;
    }
    return *this;
}

