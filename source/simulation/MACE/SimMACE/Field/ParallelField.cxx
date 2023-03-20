#include "MACE/SimMACE/Field/ParallelField.hxx"
#include "MACE/SimMACE/Messenger/FieldMessenger.hxx"

namespace MACE::SimMACE::inline Field {

ParallelField::ParallelField(G4double B) :
    NonMoveableBase(),
    G4UniformMagField(G4ThreeVector(0, 0, B)) {
    FieldMessenger::Instance().AssignTo(this);
}

} // namespace MACE::SimMACE::inline Field
