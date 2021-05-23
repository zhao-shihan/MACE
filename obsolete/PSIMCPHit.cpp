#include "PSIMACEMCPHit.hh"

#include "G4UnitsTable.hh"

#include <iomanip>

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

G4ThreadLocal G4Allocator<PSIMACEMCPHit>* PSIMACEMCPHitAllocator = 0;

PSIMACEMCPHit::PSIMACEMCPHit() :
    pos(),
    vpos(),
    globaltime(0.) {}

PSIMACEMCPHit::~PSIMACEMCPHit() {}

PSIMACEMCPHit::PSIMACEMCPHit(const PSIMACEMCPHit& right) :
    G4VHit(right) {
    pos = right.pos;
    vpos = right.vpos;
    globaltime = right.globaltime;
    // particleName = right.particleName;
}

const PSIMACEMCPHit& PSIMACEMCPHit::operator=(const PSIMACEMCPHit& right) {
    if (this != &right) {
        pos = right.pos;
        vpos = right.vpos;
        globaltime = right.globaltime;
        // particleName = right.particleName;
    }
    return *this;
}

G4bool PSIMACEMCPHit::operator==(const PSIMACEMCPHit& right) const {
    return this == &right;
}

