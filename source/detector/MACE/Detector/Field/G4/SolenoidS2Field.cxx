#include "MACE/Detector/Field/G4/SolenoidS2Field.hxx"
#include "MACE/Detector/Field/G4/Messenger/SolenoidFieldMessenger.hxx"

namespace MACE::Detector::Field::G4 {

SolenoidS2Field::SolenoidS2Field() :
    WrapAsG4Field() {
    SolenoidFieldMessenger::Instance().AssignTo(this);
}

} // namespace MACE::Detector::Field::G4
