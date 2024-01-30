#include "MACE/Detector/Field/G4/SolenoidS2Field.h++"
#include "MACE/Detector/Field/G4/Messenger/SolenoidFieldMessenger.h++"

namespace MACE::Detector::Field::G4 {

SolenoidS2Field::SolenoidS2Field() :
    WrapAsG4Field{} {
    SolenoidFieldMessenger::EnsureInstantiation();
}

} // namespace MACE::Detector::Field::G4
