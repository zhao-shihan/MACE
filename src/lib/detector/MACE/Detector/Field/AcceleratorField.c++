#include "MACE/Detector/Description/Accelerator.h++"
#include "MACE/Detector/Description/FieldOption.h++"
#include "MACE/Detector/Description/MMSField.h++"
#include "MACE/Detector/Field/AcceleratorField.h++"
#include "MACE/Utility/ParseEnv.h++"

namespace MACE::Detector::Field {

AcceleratorField::AcceleratorField() : // clang-format off
    ElectromagneticFieldBase<AcceleratorField>{}, // clang-format on
    fField{FastField{{}, {}}} {
    const auto& fieldOption{Detector::Description::FieldOption::Instance()};
    const auto& acceleratorField{Description::Accelerator::Instance()};
    if (fieldOption.UseFast()) {
        const auto& mmsField{Detector::Description::MMSField::Instance()};
        fField = FastField{0, 0, mmsField.FastField(), 0, 0, acceleratorField.FastField()};
    } else {
        fField = FieldMap{fieldOption.FieldDataFileName(), "AcceleratorField"};
    }
}

} // namespace MACE::Detector::Field
