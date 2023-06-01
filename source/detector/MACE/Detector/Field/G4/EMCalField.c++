#include "MACE/Detector/Field/G4/EMCalField.h++"
#include "MACE/Detector/Field/G4/Messenger/EMCalFieldMessenger.h++"

namespace MACE::Detector::Field::G4 {

EMCalField::EMCalField() :
    WrapAsG4Field() {
    EMCalFieldMessenger::Instance().AssignTo(this);
}

} // namespace MACE::Detector::Field::G4
