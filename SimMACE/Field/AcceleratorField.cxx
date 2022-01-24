#include "SimMACE/Field/AcceleratorField.hxx"
#include "SimMACE/Messenger/FieldMessenger.hxx"

using namespace MACE::SimMACE::Field;

AcceleratorField::AcceleratorField() :
    G4ElectroMagneticField() {
    Messenger::FieldMessenger::Instance()->Set(this);
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
    fEz = fV / (fAccelerateEnd - fAccelerateBegin);
}

void AcceleratorField::SetAccelerateBegin(G4double beginZPos) {
    fAccelerateBegin = beginZPos;
    fEz = fV / (fAccelerateEnd - fAccelerateBegin);
}

void AcceleratorField::SetAccelerateEnd(G4double endZPos) {
    fAccelerateEnd = endZPos;
    fEz = fV / (fAccelerateEnd - fAccelerateBegin);
}
