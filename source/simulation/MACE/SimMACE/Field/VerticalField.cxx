#include "MACE/SimMACE/Field/VerticalField.hxx"
#include "MACE/SimMACE/Messenger/FieldMessenger.hxx"

namespace MACE::SimMACE::Field {

VerticalField::VerticalField(G4double B) :
    NonMoveableBase(),
    G4UniformMagField(G4ThreeVector(B, 0, 0)) {
    Messenger::FieldMessenger::Instance().AssignTo(this);
}

} // namespace MACE::SimMACE::Field
