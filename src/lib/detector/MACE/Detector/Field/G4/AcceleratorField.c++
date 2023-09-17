#include "MACE/Detector/Field/G4/AcceleratorField.h++"
#include "MACE/Detector/Field/G4/Messenger/AcceleratorFieldMessenger.h++"

namespace MACE::Detector::Field::G4 {

AcceleratorField::AcceleratorField() :
    WrapAsG4Field() {
    AcceleratorFieldMessenger::Instance().AssignTo(this);
}

} // namespace MACE::Detector::Field::G4
