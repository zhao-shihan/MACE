#include "MACE/Detector/Description/EMCField.h++"
#include "MACE/Detector/Description/FieldOption.h++"
#include "MACE/Detector/Field/EMCField.h++"

namespace MACE::Detector::Field {

EMCField::EMCField() :
    MagneticFieldBase<EMCField>{
},
    fField{FastField{0, 0, 0}} {
    const auto& fieldOption{Detector::Description::FieldOption::Instance()};
    const auto& emcField{Detector::Description::EMCField::Instance()};
    if (fieldOption.UseFast()) {
        fField = FastField{0, 0, emcField.FastField()};
    } else {
        fField = FieldMap{fieldOption.FieldDataFileName(), "EMCField"};
    }
}

} // namespace MACE::Detector::Field
