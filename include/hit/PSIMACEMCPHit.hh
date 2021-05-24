#ifndef PSIMACEMCPHit_hh
#define PSIMACEMCPHit_hh 1

#include "globals.hh"

struct PSIMACEMCPHit {
    G4double t;
    G4double x;
    G4double y;
    
    PSIMACEMCPHit(G4double t_val, G4double x_val, G4double y_val);
    PSIMACEMCPHit();
};

#endif

