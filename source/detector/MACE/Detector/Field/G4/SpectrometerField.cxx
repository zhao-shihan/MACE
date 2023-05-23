#include "MACE/Detector/Field/G4/SpectrometerField.hxx"
#include "MACE/Detector/Field/G4/Messenger/SpectrometerFieldMessenger.hxx"

namespace MACE::Detector::Field::G4 {

SpectrometerField::SpectrometerField() :
    WrapAsG4Field() {
    SpectrometerFieldMessenger::Instance().AssignTo(this);
}

} // namespace MACE::Detector::Field::G4
