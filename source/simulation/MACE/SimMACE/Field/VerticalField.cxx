#include "MACE/SimMACE/Field/VerticalField.hxx"
#include "MACE/SimMACE/Messenger/FieldMessenger.hxx"

using MACE::SimMACE::Field::VerticalField;
using MACE::SimMACE::Messenger::FieldMessenger;

VerticalField::VerticalField(G4double B) :
    G4UniformMagField(G4ThreeVector(B, 0, 0)) {
    FieldMessenger::Instance().Set(this);
}
