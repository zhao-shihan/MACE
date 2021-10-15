#include "SimG4/Field/VerticalField.hh"
#include "SimG4/Messenger/FieldMessenger.hh"

using namespace MACE::SimG4::Field;

VerticalField::VerticalField(G4double B) :
    G4UniformMagField(G4ThreeVector(B, 0, 0)) {
    Messenger::FieldMessenger::Instance()->Set(this);
}
