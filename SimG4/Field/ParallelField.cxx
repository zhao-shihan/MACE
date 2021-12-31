#include "SimG4/Field/ParallelField.hxx"
#include "SimG4/Messenger/FieldMessenger.hxx"

using namespace MACE::SimG4::Field;

ParallelField::ParallelField(G4double B) :
    G4UniformMagField(G4ThreeVector(0, 0, B)) {
    Messenger::FieldMessenger::Instance()->Set(this);
}
