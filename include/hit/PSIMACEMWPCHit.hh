#ifndef PSIMACEMWPCHit_hh
#define PSIMACEMWPCHit_hh 1

#include "globals.hh"

struct PSIMACEMWPCHit {
    G4double t;
    G4double x;
    G4double y;
    G4double z;
    G4int    chamberNb;
    
    PSIMACEMWPCHit(G4double t_val, G4double x_val, G4double y_val, G4double z_val, G4int chamberNb_val);
    PSIMACEMWPCHit();
};

#endif

