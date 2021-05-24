#include "fields/PSIMACESeparatorField.hh"
#include "G4SystemOfUnits.hh"

using namespace CLHEP;

PSIMACESeparatorField::PSIMACESeparatorField() :
    G4ElectroMagneticField(),
    fBy(0.1 * tesla),
    fBz(0.1 * tesla),
    fEx(49.82583 * kilovolt / cm) {}

PSIMACESeparatorField::~PSIMACESeparatorField() {}

void PSIMACESeparatorField::GetFieldValue(const G4double[4], double* BE) const {
    BE[0] = 0.;
    BE[1] = fBy;
    BE[2] = fBz;
    BE[3] = fEx;
    BE[4] = 0.;
    BE[5] = 0.;
}

