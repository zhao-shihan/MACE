#include "MACE/Detector/Description/FieldOption.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Detector/Field/SolenoidFieldB1.h++"

namespace MACE::Detector::Field {

SolenoidFieldB1::SolenoidFieldB1() : // clang-format off
    MagneticFieldBase<SolenoidFieldB1>{}, // clang-format on
    fField{FastField{{}, {}, {}, {}}} {
    const auto& fieldOption{Detector::Description::FieldOption::Instance()};
    const auto& solenoid{Detector::Description::Solenoid::Instance()};
    if (fieldOption.UseFast()) { // clang-format off
        fField = FastField{solenoid.FastField(), solenoid.B1Radius(), solenoid.B1Center(), {0, 0, 1}}; // clang-format on
    } else {
        fField = FieldMap{fieldOption.FieldDataFileName(), "SolenoidFieldB1"};
    }
}

} // namespace MACE::Detector::Field
