#include "MACE/Detector/Field/G4/EMCField.h++"
#include "MACE/Detector/Field/G4/Messenger/EMCFieldMessenger.h++"

namespace MACE::Detector::Field::G4 {

EMCField::EMCField() :
    WrapAsG4Field() {
    EMCFieldMessenger::Instance().AssignTo(this);
}

} // namespace MACE::Detector::Field::G4
