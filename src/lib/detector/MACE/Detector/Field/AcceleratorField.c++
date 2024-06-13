#include "MACE/Detector/Description/Accelerator.h++"
#include "MACE/Detector/Description/FieldOption.h++"
#include "MACE/Detector/Description/MMSField.h++"
#include "MACE/Detector/Field/AcceleratorField.h++"
#include "MACE/Utility/ParseEnv.h++"

namespace MACE::Detector::Field {

AcceleratorField::FastField::FastField(double b, double e) :
    ElectromagneticFieldBase<FastField>{},
    fB{b},
    fE{e} {}

AcceleratorField::AcceleratorField() : // clang-format off
    ElectromagneticFieldBase<AcceleratorField>{}, // clang-format on
    fField{FastField{0, 0}} {
    const auto& fieldOption{Detector::Description::FieldOption::Instance()};
    const auto& acceleratorField{Description::Accelerator::Instance()};
    if (fieldOption.UseFast()) {
        const auto& mmsField{Detector::Description::MMSField::Instance()};
        fField = FastField{mmsField.FastField(), acceleratorField.FastField()};
    } else {
        fField = FieldMap{fieldOption.FieldDataFileName(), "AcceleratorField"};
    }
}

} // namespace MACE::Detector::Field
