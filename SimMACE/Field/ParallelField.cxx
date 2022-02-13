#include "SimMACE/Field/ParallelField.hxx"
#include "SimMACE/Messenger/FieldMessenger.hxx"

using namespace MACE::SimMACE::Field;

ParallelField::ParallelField(G4double B) :
    G4UniformMagField(G4ThreeVector(0, 0, B)) {
    Messenger::FieldMessenger::Instance().Set(this);
}
