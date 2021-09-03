#include "detector/field/VerticalTransportField.hh"
#include "messenger/FieldMessenger.hh"

using namespace MACE::SimG4::Field;

VerticalTransportField::VerticalTransportField(G4double B) :
    G4UniformMagField(G4ThreeVector(B, 0, 0)) {
    FieldMessenger::Instance()->Set(this);
}
