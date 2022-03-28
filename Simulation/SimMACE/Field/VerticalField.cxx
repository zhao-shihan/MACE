#include "Simulation/SimMACE/Field/VerticalField.hxx"
#include "Simulation/SimMACE/Messenger/FieldMessenger.hxx"

using MACE::Simulation::SimMACE::Field::VerticalField;
using MACE::Simulation::SimMACE::Messenger::FieldMessenger;

VerticalField::VerticalField(G4double B) :
    G4UniformMagField(G4ThreeVector(B, 0, 0)) {
    FieldMessenger::Instance().Set(this);
}
