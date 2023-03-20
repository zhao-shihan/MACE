#include "MACE/SimMACE/Field/VerticalField.hxx"
#include "MACE/SimMACE/Messenger/FieldMessenger.hxx"

namespace MACE::SimMACE::inline Field {

VerticalField::VerticalField(G4double B) :
    NonMoveableBase(),
    G4UniformMagField(G4ThreeVector(B, 0, 0)) {
    FieldMessenger::Instance().AssignTo(this);
}

} // namespace MACE::SimMACE::inline Field
