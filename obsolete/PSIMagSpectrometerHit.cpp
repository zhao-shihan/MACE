#include "PSIMACEMagSpectrometerHit.hh"

#include "G4UnitsTable.hh"

#include <iomanip>

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

G4ThreadLocal G4Allocator<PSIMACEMagSpectrometerHit>* PSIMACEMagSpectrometerHitAllocator = 0;

PSIMACEMagSpectrometerHit::PSIMACEMagSpectrometerHit() :
    pos(0., 0., 0.),
    // particleName("undefined"),
    globaltime(0.),
    vpos(0., 0., 0.),
    fChamberNb(-1) {}

PSIMACEMagSpectrometerHit::~PSIMACEMagSpectrometerHit() {}

PSIMACEMagSpectrometerHit::PSIMACEMagSpectrometerHit(const PSIMACEMagSpectrometerHit& right) :
    G4VHit(right) {
    pos = right.pos;
    globaltime = right.globaltime;
    // particleName = right.particleName;
    vpos = right.vpos;
    fChamberNb = right.fChamberNb;
}

const PSIMACEMagSpectrometerHit& PSIMACEMagSpectrometerHit::operator=(const PSIMACEMagSpectrometerHit& right) {
    if (this != &right) {
        pos = right.pos;
        globaltime = right.globaltime;
        // particleName = right.particleName;
        vpos = right.vpos;
        fChamberNb = right.fChamberNb;
    }
    return *this;
}

