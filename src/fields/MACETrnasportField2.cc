#include "fields/MACETransportField2.hh"
#include "G4SystemOfUnits.hh"

using namespace CLHEP;

MACETransportField2::MACETransportField2(G4double transportField2Z) :
    G4MagneticField(),
    // fBy(-0.00080829 * tesla),
    fBz(0.1 * tesla),
    fTransportField2Z(transportField2Z) {}

MACETransportField2::~MACETransportField2() {}

void MACETransportField2::GetFieldValue(const G4double point[4], double* B) const {
    constexpr G4double R0 = 35 * cm;
    constexpr G4double x0 = R0;
    G4double z0 = fTransportField2Z - R0;
    double r = sqrt((point[0] - x0) * (point[0] - x0) + (point[2] - z0) * (point[2] - z0));
    B[0] = (point[2] - z0) / r * fBz;
    B[1] = /* fBy */0.;
    B[2] = -(point[0] - x0) / r * fBz;
}