#include "MACE/Core/Geometry/Description/TransportLine.hxx"
#include "MACE/Simulation/SimMACE/Field/SecondBendField.hxx"
#include "MACE/Simulation/SimMACE/Messenger/FieldMessenger.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

namespace MACE::Simulation::SimMACE::Field {

using namespace MACE::Utility::LiteralUnit::MagneticFluxDensity;

SecondBendField::SecondBendField() :
    G4MagneticField(),
    fB(0.1_T) {
    Messenger::FieldMessenger::Instance().Set(this);
    const auto& fieldTransform = Core::Geometry::Description::TransportLine::Instance().SecondBendTransform();
    fX0 = fieldTransform.dx();
    fZ0 = fieldTransform.dz();
}

void SecondBendField::GetFieldValue(const G4double* x, G4double* B) const {
    const auto r = std::sqrt((x[0] - fX0) * (x[0] - fX0) + (x[2] - fZ0) * (x[2] - fZ0));
    B[0] = -(x[2] - fZ0) / r * fB;
    B[1] = 0;
    B[2] = (x[0] - fX0) / r * fB;
}

} // namespace MACE::Simulation::SimMACE::Field
