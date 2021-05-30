#ifndef MACECsIHit_hh
#define MACECsIHit_hh 1

#include "globals.hh"

struct MACECsIHit {
    G4double t;
    G4double E;
    
    MACECsIHit(G4double t_val, G4double E_val);
    MACECsIHit();
};

#endif

