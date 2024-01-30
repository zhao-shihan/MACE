#include "MACE/Detector/Field/G4/SolenoidS3Field.h++"
#include "MACE/Detector/Field/G4/Messenger/SolenoidFieldMessenger.h++"

namespace MACE::Detector::Field::G4 {

SolenoidS3Field::SolenoidS3Field() :
    WrapAsG4Field{} {
    SolenoidFieldMessenger::EnsureInstantiation();
}

} // namespace MACE::Detector::Field::G4
