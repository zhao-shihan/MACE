#ifndef MACEMCPHit_hh
#define MACEMCPHit_hh 1

#include "globals.hh"

struct MACEMCPHit {
    G4double t;
    G4double x;
    G4double y;
    
    MACEMCPHit(G4double t_val, G4double x_val, G4double y_val);
    MACEMCPHit();
};

#endif

