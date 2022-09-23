#include "MACE/Core/Geometry/Description/LinacField.hxx"
#include "MACE/SimMACE/Field/LinacField.hxx"
#include "MACE/SimMACE/Messenger/FieldMessenger.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

namespace MACE::SimMACE::Field {

using LinacDescription = MACE::Core::Geometry::Description::LinacField;
using Messenger::FieldMessenger;
using namespace MACE::Utility::LiteralUnit::ElectricPotential;
using namespace MACE::Utility::LiteralUnit::Length;
using namespace MACE::Utility::LiteralUnit::MagneticFluxDensity;

LinacField::LinacField() :
    NonMoveableBase(),
    G4ElectroMagneticField(),
    fBz(0.1_T),
    fV(7_kV),
    fDecayZMean(13.05_mm),
    fEz(7_kV / (LinacDescription::Instance().DownStreamLength() - 13.05_mm)) {
    FieldMessenger::Instance().AssignTo(this);
}

void LinacField::GetFieldValue(const G4double*, G4double* F) const {
    F[0] = 0.;
    F[1] = 0.;
    F[2] = fBz;
    F[3] = 0.;
    F[4] = 0.;
    F[5] = fEz;
}

void LinacField::SetLinacPotential(G4double V) {
    fV = V;
    fEz = fV / (LinacDescription::Instance().DownStreamLength() - fDecayZMean);
}

} // namespace MACE::SimMACE::Field
