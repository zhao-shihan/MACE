#include "MACE/Detector/Description/EMCField.h++"
#include "MACE/Detector/Field/EMCField.h++"
#include "MACE/Utility/ParseEnv.h++"

namespace MACE::Detector::Field {

EMCField::FastField::FastField(double b) :
    MagneticFieldBase<FastField>{},
    fEMCField{b} {}

EMCField::EMCField() :
    MagneticFieldBase<EMCField>{},
    fField{0} {
    const auto& emcField{Detector::Description::EMCField::Instance().Field()};
    if (emcField.UseFast()) {
        fField = FastField{emcField.FastField()};
    } else {
        fField = FieldMap{ParseEnv(emcField.FieldMap()), "EMCField"};
    }
}

} // namespace MACE::Detector::Field
