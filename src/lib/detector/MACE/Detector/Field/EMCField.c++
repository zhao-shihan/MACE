#include "MACE/Detector/Description/EMCField.h++"
#include "MACE/Detector/Description/FieldOption.h++"
#include "MACE/Detector/Field/EMCField.h++"

namespace MACE::Detector::Field {

EMCField::FastField::FastField(double b) :
    MagneticFieldBase<FastField>{},
    fB{b} {}

EMCField::EMCField() :
    MagneticFieldBase<EMCField>{},
    fField{0} {
    const auto& fieldOption{Detector::Description::FieldOption::Instance()};
    const auto& emcField{Detector::Description::EMCField::Instance()};
    if (fieldOption.UseFast()) {
        fField = FastField{emcField.FastField()};
    } else {
        fField = FieldMap{fieldOption.FieldDataFileName(), "EMCField"};
    }
}

} // namespace MACE::Detector::Field
