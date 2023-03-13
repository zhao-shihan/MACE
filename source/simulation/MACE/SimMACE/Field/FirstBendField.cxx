#include "MACE/Geometry/Description/TransportLine.hxx"
#include "MACE/Math/Hypot.hxx"
#include "MACE/SimMACE/Field/FirstBendField.hxx"
#include "MACE/SimMACE/Messenger/FieldMessenger.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

namespace MACE::SimMACE::Field {

using namespace MACE::LiteralUnit::MagneticFluxDensity;

FirstBendField::FirstBendField() :
    NonMoveableBase(),
    G4MagneticField(),
    fGeomTransform(Geometry::Description::TransportLine::Instance().FirstBendTransform()),
    fBendRadius(Geometry::Description::TransportLine::Instance().FirstBendRadius()),
    fB0R0(0.1_T * fBendRadius) {
    Messenger::FieldMessenger::Instance().AssignTo(this);
}

void FirstBendField::GetFieldValue(const G4double* x, G4double* B) const {
    const auto deltaX = x[0] - fGeomTransform.dx();
    const auto deltaZ = x[2] - fGeomTransform.dz();
    const auto r2 = Math::Hypot2(deltaX, deltaZ);
    B[0] = fB0R0 * deltaZ / r2;
    B[1] = 0;
    B[2] = -fB0R0 * deltaX / r2;
}

} // namespace MACE::SimMACE::Field
