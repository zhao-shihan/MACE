#include "MACE/Core/Geometry/Description/TransportLine.hxx"
#include "MACE/SimMACE/Field/SecondBendField.hxx"
#include "MACE/SimMACE/Messenger/FieldMessenger.hxx"
#include "MACE/Utility/LiteralUnit.hxx"
#include "MACE/Utility/Math/Hypot.hxx"

namespace MACE::SimMACE::Field {

using namespace MACE::Utility::LiteralUnit::MagneticFluxDensity;
using MACE::Utility::Math::Hypot2;
using TransportLineDescription = Core::Geometry::Description::TransportLine;

SecondBendField::SecondBendField() :
    NonCopyableBase(),
    G4MagneticField(),
    fGeomTransform(TransportLineDescription::Instance().SecondBendTransform()),
    fBendRadius(TransportLineDescription::Instance().GetSecondBendRadius()),
    fB0R0(0.1_T * fBendRadius) {
    Messenger::FieldMessenger::Instance().SetTo(this);
}

void SecondBendField::GetFieldValue(const G4double* x, G4double* B) const {
    const auto deltaX = x[0] - fGeomTransform.dx();
    const auto deltaZ = x[2] - fGeomTransform.dz();
    const auto r2 = Hypot2(deltaX, deltaZ);
    B[0] = -fB0R0 * deltaZ / r2;
    B[1] = 0;
    B[2] = fB0R0 * deltaX / r2;
}

} // namespace MACE::SimMACE::Field
