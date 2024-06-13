#include "MACE/Detector/Description/FieldOption.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Detector/Field/SolenoidFieldB2.h++"

namespace MACE::Detector::Field {

SolenoidFieldB2::SolenoidFieldB2() : // clang-format off
    MagneticFieldBase<SolenoidFieldB2>{}, // clang-format on
    fField{FastField{{}, {}, {}, {}}} {
    const auto& fieldOption{Detector::Description::FieldOption::Instance()};
    const auto& solenoid{Detector::Description::Solenoid::Instance()};
    if (fieldOption.UseFast()) { // clang-format off
        fField = FastField{solenoid.FastField(), solenoid.B2Radius(), solenoid.B2Center(), {0, 0, -1}}; // clang-format on
    } else {
        fField = FieldMap{fieldOption.FieldDataFileName(), "SolenoidFieldB2"};
    }
}

} // namespace MACE::Detector::Field
