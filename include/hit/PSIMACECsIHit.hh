#ifndef PSIMACECsIHit_hh
#define PSIMACECsIHit_hh 1

#include "globals.hh"

struct PSIMACECsIHit {
    G4double t;
    G4double E;
    
    PSIMACECsIHit(G4double t_val, G4double E_val);
    PSIMACECsIHit();
};

#endif

