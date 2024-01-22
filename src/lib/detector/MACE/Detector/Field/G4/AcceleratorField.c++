#include "MACE/Detector/Field/G4/AcceleratorField.h++"
#include "MACE/Detector/Field/G4/Messenger/AcceleratorFieldMessenger.h++"

namespace MACE::Detector::Field::G4 {

AcceleratorField::AcceleratorField() :
    WrapAsG4Field{} {
    AcceleratorFieldMessenger::EnsureInstantiation();
}

} // namespace MACE::Detector::Field::G4
