#include "SimMACE/Field/FirstBendField.hxx"
#include "SimMACE/Messenger/FieldMessenger.hxx"

#include "Geometry/Description/DescendantsOfWorld/FirstBendField.hxx"

using namespace MACE::SimMACE::Field;

FirstBendField::FirstBendField() :
    G4MagneticField() {
    Messenger::FieldMessenger::Instance().Set(this);
}

void FirstBendField::GetFieldValue(const G4double* x, G4double* B) const {
    const auto& geom = Geometry::Description::FirstBendField::Instance();
    auto x0 = geom.GetTransform().dx();
    auto z0 = geom.GetTransform().dz();

    auto r = std::hypot(x[0] - x0, x[2] - z0);
    B[0] = (x[2] - z0) / r * fB;
    B[1] = 0;
    B[2] = -(x[0] - x0) / r * fB;
}
