#include "MACE/Detector/Field/AcceleratorField.h++"

namespace MACE::Detector::Field {

AcceleratorField::FastField::FastField() :
    ElectromagneticFieldBase<FastField>{},
    fMMSField{Description::MMSField::Instance()},
    fAccelerator{Description::Accelerator::Instance()} {}

AcceleratorField::AcceleratorField(std::string_view fileName, std::string_view nTupleName) : // clang-format off
    ElectromagneticFieldBase<AcceleratorField>{}, // clang-format on
    fField{TrilerpField{fileName, nTupleName}} {}

} // namespace MACE::Detector::Field
