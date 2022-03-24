#include "Geometry/Description/AcceleratorField.hxx"
#include "LiteralUnit.hxx"
#include "SimMACE/Field/AcceleratorField.hxx"
#include "SimMACE/Messenger/FieldMessenger.hxx"

namespace MACE::Simulation::SimMACE::Field {

using namespace MACE::Utility::LiteralUnit;
using Messenger::FieldMessenger;
using LinacDescription = MACE::Geometry::Description::AcceleratorField;

AcceleratorField::AcceleratorField() :
    G4ElectroMagneticField(),
    fBz(0.1_T),
    fV(7_kV),
    fEz(fV / (LinacDescription::Instance().GetDownStreamLength() - fDecayZMean)),
    fDecayZMean(13.05_mm) {
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
    fEz = fV / (LinacDescription::Instance().GetDownStreamLength() - fDecayZMean);
}

} // namespace MACE::Simulation::SimMACE::Field
