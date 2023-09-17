#include "MACE/Detector/Field/G4/SpectrometerField.h++"
#include "MACE/Detector/Field/G4/Messenger/SpectrometerFieldMessenger.h++"

namespace MACE::Detector::Field::G4 {

SpectrometerField::SpectrometerField() :
    WrapAsG4Field() {
    SpectrometerFieldMessenger::Instance().AssignTo(this);
}

} // namespace MACE::Detector::Field::G4
