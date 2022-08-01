#include "MACE/SimMACE/Field/ParallelField.hxx"
#include "MACE/SimMACE/Messenger/FieldMessenger.hxx"

namespace MACE::SimMACE::Field {

ParallelField::ParallelField(G4double B) :
    NonMoveableBase(),
    G4UniformMagField(G4ThreeVector(0, 0, B)) {
    Messenger::FieldMessenger::Instance().SetTo(this);
}

} // namespace MACE::SimMACE::Field
