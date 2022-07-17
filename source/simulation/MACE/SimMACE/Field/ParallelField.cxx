#include "MACE/SimMACE/Field/ParallelField.hxx"
#include "MACE/SimMACE/Messenger/FieldMessenger.hxx"

using MACE::SimMACE::Field::ParallelField;
using MACE::SimMACE::Messenger::FieldMessenger;

ParallelField::ParallelField(G4double B) :
    G4UniformMagField(G4ThreeVector(0, 0, B)) {
    FieldMessenger::Instance().Set(this);
}
