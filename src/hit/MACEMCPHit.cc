#include "hit/MACEMCPHit.hh"

MACEMCPHit::MACEMCPHit(G4double t_val, G4double x_val, G4double y_val) :
    t(t_val),
    x(x_val),
    y(y_val) {}

MACEMCPHit::MACEMCPHit() :
    t(-1.),
    x(0.),
    y(0.) {}
