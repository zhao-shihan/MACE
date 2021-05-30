#include "fields/MACEAcceleratorField.hh"

#include "G4SystemOfUnits.hh"
#include "MACEConfigs.hh"

using namespace CLHEP;

MACEAcceleratorField::MACEAcceleratorField() :
    G4ElectroMagneticField(),
    fBz(0.1 * tesla),
#if MACE_EXPERIMENT_TYPE == 1
    fEz(-0.175 * kilovolt / cm)
#elif MACE_EXPERIMENT_TYPE == -1
    fEz(0.175 * kilovolt / cm)
#else
#error "unknown experiment."
#endif
{}

MACEAcceleratorField::~MACEAcceleratorField() {}

void MACEAcceleratorField::GetFieldValue(const G4double[4], double* BE) const {
    BE[0] = 0.;
    BE[1] = 0.;
    BE[2] = fBz;
    BE[3] = 0.;
    BE[4] = 0.;
    BE[5] = fEz;
}

