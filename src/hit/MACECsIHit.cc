#include "hit/MACECsIHit.hh"

MACECsIHit::MACECsIHit(G4double t_val, G4double E_val) :
    t(t_val),
    E(E_val) {}

MACECsIHit::MACECsIHit() :
    t(-1.),
    E(-1.) {}

