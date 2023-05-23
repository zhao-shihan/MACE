#include "MACE/Detector/Field/G4/SolenoidS1Field.hxx"
#include "MACE/Detector/Field/G4/Messenger/SolenoidFieldMessenger.hxx"

namespace MACE::Detector::Field::G4 {

SolenoidS1Field::SolenoidS1Field() :
    WrapAsG4Field() {
    SolenoidFieldMessenger::Instance().AssignTo(this);
}

} // namespace MACE::Detector::Field::G4
