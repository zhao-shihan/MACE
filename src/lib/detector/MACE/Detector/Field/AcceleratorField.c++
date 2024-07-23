#include "MACE/Detector/Description/Accelerator.h++"
#include "MACE/Detector/Description/FieldOption.h++"
#include "MACE/Detector/Description/MMSField.h++"
#include "MACE/Detector/Field/AcceleratorField.h++"

namespace MACE::Detector::Field {

AcceleratorField::AcceleratorField() : // clang-format off
    ElectromagneticFieldBase<AcceleratorField>{}, // clang-format on
    fField{} {
    const auto& fieldOption{Detector::Description::FieldOption::Instance()};
    if (not fieldOption.UseFast()) {
        fField = FieldMap{fieldOption.ParsedFieldDataFilePath().generic_string(), "AcceleratorField"};
    }
}

AcceleratorField::FastField::FastField() :
    fB{Detector::Description::MMSField::Instance().FastField()} {
    const auto& accelerator{Description::Accelerator::Instance()};
    fZ0 = accelerator.MaxPotentialPosition();
    fE1 = -accelerator.MaxPotential() / accelerator.DecelerateFieldLength();
    fE2 = accelerator.MaxPotential() / accelerator.AccelerateFieldLength();
}

} // namespace MACE::Detector::Field
