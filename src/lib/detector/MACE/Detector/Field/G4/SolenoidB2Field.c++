#include "MACE/Detector/Field/G4/SolenoidB2Field.h++"
#include "MACE/Detector/Field/G4/Messenger/SolenoidFieldMessenger.h++"

namespace MACE::Detector::Field::G4 {

SolenoidB2Field::SolenoidB2Field() :
    WrapAsG4Field() {
    SolenoidFieldMessenger::Instance().Register(this);
}

} // namespace MACE::Detector::Field::G4
