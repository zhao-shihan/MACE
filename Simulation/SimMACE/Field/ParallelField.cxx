#include "Simulation/SimMACE/Field/ParallelField.hxx"
#include "Simulation/SimMACE/Messenger/FieldMessenger.hxx"

using MACE::Simulation::SimMACE::Field::ParallelField;
using MACE::Simulation::SimMACE::Messenger::FieldMessenger;

ParallelField::ParallelField(G4double B) :
    G4UniformMagField(G4ThreeVector(0, 0, B)) {
    FieldMessenger::Instance().Set(this);
}
