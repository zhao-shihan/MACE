#include "SimMACE/Field/VerticalField.hxx"
#include "SimMACE/Messenger/FieldMessenger.hxx"

using MACE::Simulation::SimMACE::Field::VerticalField;
using MACE::Simulation::SimMACE::Messenger::FieldMessenger;

VerticalField::VerticalField(G4double B) :
    G4UniformMagField(G4ThreeVector(B, 0, 0)) {
    FieldMessenger::Instance().Set(this);
}
