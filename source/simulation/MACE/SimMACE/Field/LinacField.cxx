#include "MACE/Detector/Description/LinacField.hxx"
#include "MACE/SimMACE/Field/LinacField.hxx"
#include "MACE/SimMACE/Messenger/FieldMessenger.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

namespace MACE::SimMACE::Field {

using namespace MACE::LiteralUnit::ElectricPotential;
using namespace MACE::LiteralUnit::Length;
using namespace MACE::LiteralUnit::MagneticFluxDensity;

LinacField::LinacField() :
    NonMoveableBase(),
    G4ElectroMagneticField(),
    fBz(0.1_T),
    fV(1_kV),
    fEz(1_kV / Detector::Description::LinacField::Instance().DownStreamLength()) {
    Messenger::FieldMessenger::Instance().AssignTo(this);
}

void LinacField::GetFieldValue(const G4double*, G4double* F) const {
    F[0] = 0;
    F[1] = 0;
    F[2] = fBz;
    F[3] = 0;
    F[4] = 0;
    F[5] = fEz;
}

void LinacField::SetLinacPotential(G4double V) {
    fV = V;
    fEz = fV / Detector::Description::LinacField::Instance().DownStreamLength();
}

} // namespace MACE::SimMACE::Field
