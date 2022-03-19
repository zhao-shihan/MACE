#include "SimMACE/Field/AcceleratorField.hxx"
#include "SimMACE/Messenger/FieldMessenger.hxx"
#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/AcceleratorField.hxx"

using namespace MACE::SimMACE::Field;

using AccFldGeomDscrpt = MACE::Geometry::Description::AcceleratorField;

AcceleratorField::AcceleratorField() :
    G4ElectroMagneticField(),
    fEz(7_kV / (AccFldGeomDscrpt::Instance().GetDownStreamLength() - fDecayZMean)) {
    FieldMessenger::Instance().Set(this);
}

void AcceleratorField::GetFieldValue(const G4double*, G4double* F) const {
    F[0] = 0.;
    F[1] = 0.;
    F[2] = fBz;
    F[3] = 0.;
    F[4] = 0.;
    F[5] = fEz;
}

void AcceleratorField::SetAcceleratorPotential(G4double V) {
    fV = V;
    fEz = fV / (AccFldGeomDscrpt::Instance().GetDownStreamLength() - fDecayZMean);
}
