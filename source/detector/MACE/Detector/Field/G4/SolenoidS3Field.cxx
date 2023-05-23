#include "MACE/Detector/Field/G4/SolenoidS3Field.hxx"
#include "MACE/Detector/Field/G4/Messenger/SolenoidFieldMessenger.hxx"

namespace MACE::Detector::Field::G4 {

SolenoidS3Field::SolenoidS3Field() :
    WrapAsG4Field() {
    SolenoidFieldMessenger::Instance().AssignTo(this);
}

} // namespace MACE::Detector::Field::G4
