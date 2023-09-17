#include "MACE/Detector/Field/G4/Messenger/SolenoidFieldMessenger.h++"
#include "MACE/Detector/Field/G4/SolenoidB1Field.h++"

namespace MACE::Detector::Field::G4 {

SolenoidB1Field::SolenoidB1Field() :
    WrapAsG4Field() {
    SolenoidFieldMessenger::Instance().AssignTo(this);
}

} // namespace MACE::Detector::Field::G4
