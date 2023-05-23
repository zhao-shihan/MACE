#include "MACE/Detector/Field/G4/EMCalField.hxx"
#include "MACE/Detector/Field/G4/Messenger/EMCalFieldMessenger.hxx"

namespace MACE::Detector::Field::G4 {

EMCalField::EMCalField() :
    WrapAsG4Field() {
    EMCalFieldMessenger::Instance().AssignTo(this);
}

} // namespace MACE::Detector::Field::G4
