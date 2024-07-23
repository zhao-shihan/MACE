#include "MACE/Detector/Description/EMCField.h++"
#include "MACE/Detector/Description/FieldOption.h++"
#include "MACE/Detector/Field/EMCField.h++"

namespace MACE::Detector::Field {

EMCField::EMCField() : // clang-format off
    MagneticFieldBase<EMCField>{}, // clang-format on
    fField{FastField{{}}} {
    const auto& fieldOption{Detector::Description::FieldOption::Instance()};
    const auto& emcField{Detector::Description::EMCField::Instance()};
    if (fieldOption.UseFast()) {
        fField = FastField{0, 0, emcField.FastField()};
    } else {
        fField = FieldMap{fieldOption.ParsedFieldDataFilePath().generic_string(), "EMCField"};
    }
}

} // namespace MACE::Detector::Field
