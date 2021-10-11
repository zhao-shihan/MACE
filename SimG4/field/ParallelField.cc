#include "SimG4/field/ParallelField.hh"
#include "SimG4/messenger/FieldMessenger.hh"

using namespace MACE::SimG4::Field;

ParallelField::ParallelField(G4double B) :
    G4UniformMagField(G4ThreeVector(0, 0, B)) {
    Messenger::FieldMessenger::Instance()->Set(this);
}
