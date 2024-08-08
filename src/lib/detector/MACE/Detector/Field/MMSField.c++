#include "MACE/Detector/Description/FieldOption.h++"
#include "MACE/Detector/Description/MMSField.h++"
#include "MACE/Detector/Field/MMSField.h++"

namespace MACE::Detector::Field {

MMSField::MMSField() :
    MagneticFieldBase<MMSField>{},
    fField{FastField{{}}} {
    const auto& fieldOption{Detector::Description::FieldOption::Instance()};
    const auto& eCalField{Detector::Description::MMSField::Instance()};
    if (fieldOption.UseFast()) {
        fField = FastField{0, 0, eCalField.FastField()};
    } else {
        fField = FieldMap{fieldOption.ParsedFieldDataFilePath().generic_string(), "MMSField"};
    }
}

} // namespace MACE::Detector::Field
