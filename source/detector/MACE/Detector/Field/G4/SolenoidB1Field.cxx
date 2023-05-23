#include "MACE/Detector/Field/G4/Messenger/SolenoidFieldMessenger.hxx"
#include "MACE/Detector/Field/G4/SolenoidB1Field.hxx"

namespace MACE::Detector::Field::G4 {

SolenoidB1Field::SolenoidB1Field() :
    WrapAsG4Field() {
    SolenoidFieldMessenger::Instance().AssignTo(this);
}

} // namespace MACE::Detector::Field::G4
