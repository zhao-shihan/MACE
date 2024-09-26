#include "MACE/Detector/Description/ECALField.h++"
#include "MACE/Detector/Description/FieldOption.h++"
#include "MACE/Detector/Field/ECALField.h++"

namespace MACE::Detector::Field {

ECALField::ECALField() : // clang-format off
    MagneticFieldBase<ECALField>{}, // clang-format on
    fField{FastField{{}}} {
    const auto& fieldOption{Detector::Description::FieldOption::Instance()};
    const auto& ecalField{Detector::Description::ECALField::Instance()};
    if (fieldOption.UseFast()) {
        fField = FastField{0, 0, ecalField.FastField()};
    } else {
        fField = FieldMap{fieldOption.ParsedFieldDataFilePath().generic_string(), "EMCField"};
    }
}

} // namespace MACE::Detector::Field
