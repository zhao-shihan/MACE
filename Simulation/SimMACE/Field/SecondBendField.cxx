#include "Geometry/Description/SecondBendField.hxx"
#include "LiteralUnit.hxx"
#include "SimMACE/Field/SecondBendField.hxx"
#include "SimMACE/Messenger/FieldMessenger.hxx"

namespace MACE::Simulation::SimMACE::Field {

using namespace MACE::Utility::LiteralUnit::MagneticFluxDensity;
using Messenger::FieldMessenger;

SecondBendField::SecondBendField() :
    G4MagneticField(),
    fB(0.1_T) {
    FieldMessenger::Instance().Set(this);
}

void SecondBendField::GetFieldValue(const G4double* x, G4double* B) const {
    const auto& geom = Geometry::Description::SecondBendField::Instance();
    auto x0 = geom.GetTransform().dx();
    auto z0 = geom.GetTransform().dz();

    auto r = std::hypot(x[0] - x0, x[2] - z0);
    B[0] = -(x[2] - z0) / r * fB;
    B[1] = 0;
    B[2] = (x[0] - x0) / r * fB;
}

} // namespace MACE::Simulation::SimMACE::Field
