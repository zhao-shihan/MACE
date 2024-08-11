#include "MACE/Detector/Description/ECalField.h++"
#include "MACE/Detector/Description/FieldOption.h++"
#include "MACE/Detector/Field/ECalField.h++"

namespace MACE::Detector::Field {

ECalField::ECalField() : // clang-format off
    MagneticFieldBase<ECalField>{}, // clang-format on
    fField{FastField{{}}} {
    const auto& fieldOption{Detector::Description::FieldOption::Instance()};
    const auto& eCalField{Detector::Description::ECalField::Instance()};
    if (fieldOption.UseFast()) {
        fField = FastField{0, 0, eCalField.FastField()};
    } else {
        fField = FieldMap{fieldOption.ParsedFieldDataFilePath().generic_string(), "EMCField"};
    }
}

} // namespace MACE::Detector::Field
