#include "hit/PSIMACEMWPCHit.hh"

PSIMACEMWPCHit::PSIMACEMWPCHit(G4double t_val, G4double x_val, G4double y_val, G4double z_val, G4int chamberNb_val) :
    t(t_val),
    x(x_val),
    y(y_val),
    z(z_val),
    chamberNb(chamberNb_val) {}

PSIMACEMWPCHit::PSIMACEMWPCHit() :
    t(-1.),
    x(0.),
    y(0.),
    z(0.),
    chamberNb(-1) {}

