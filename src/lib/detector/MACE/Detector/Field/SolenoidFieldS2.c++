#include "MACE/Detector/Description/FieldOption.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Detector/Field/SolenoidFieldS2.h++"

namespace MACE::Detector::Field {

SolenoidFieldS2::SolenoidFieldS2() : // clang-format off
    MagneticFieldBase<SolenoidFieldS2>{}, // clang-format on
    fField{FastField{{}}} {
    const auto& fieldOption{Detector::Description::FieldOption::Instance()};
    const auto& solenoid{Detector::Description::Solenoid::Instance()};
    if (fieldOption.UseFast()) {
        fField = FastField{solenoid.FastField(), 0, 0};
    } else {
        fField = FieldMap{fieldOption.FieldDataFileName(), "SolenoidFieldS2"};
    }
}

} // namespace MACE::Detector::Field
