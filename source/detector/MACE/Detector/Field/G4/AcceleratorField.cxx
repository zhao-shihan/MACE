#include "MACE/Detector/Field/G4/AcceleratorField.hxx"
#include "MACE/Detector/Field/G4/Messenger/AcceleratorFieldMessenger.hxx"

namespace MACE::Detector::Field::G4 {

AcceleratorField::AcceleratorField() :
    WrapAsG4Field() {
    AcceleratorFieldMessenger::Instance().AssignTo(this);
}

} // namespace MACE::Detector::Field::G4
