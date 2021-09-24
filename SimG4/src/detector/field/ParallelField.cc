#include "detector/field/ParallelField.hh"
#include "messenger/FieldMessenger.hh"

using namespace MACE::SimG4::Field;

ParallelField::ParallelField(G4double B) :
    G4UniformMagField(G4ThreeVector(0, 0, B)) {
    FieldMessenger::Instance()->Set(this);
}
