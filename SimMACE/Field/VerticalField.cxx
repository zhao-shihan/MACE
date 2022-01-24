#include "SimMACE/Field/VerticalField.hxx"
#include "SimMACE/Messenger/FieldMessenger.hxx"

using namespace MACE::SimMACE::Field;

VerticalField::VerticalField(G4double B) :
    G4UniformMagField(G4ThreeVector(B, 0, 0)) {
    Messenger::FieldMessenger::Instance()->Set(this);
}
