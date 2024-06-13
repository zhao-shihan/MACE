#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Detector/Description/FieldOption.h++"
#include "MACE/Detector/Field/SolenoidFieldS1.h++"

namespace MACE::Detector::Field {

SolenoidFieldS1::SolenoidFieldS1() : // clang-format off
    MagneticFieldBase<SolenoidFieldS1>{}, // clang-format on
    fField{FastField{{}}} {
    const auto& fieldOption{Detector::Description::FieldOption::Instance()};
    const auto& solenoid{Detector::Description::Solenoid::Instance()};
    if (fieldOption.UseFast()) {
        fField = FastField{0, 0, solenoid.FastField()};
    } else {
        fField = FieldMap{fieldOption.FieldDataFileName(), "SolenoidFieldS1"};
    }
}

} // namespace MACE::Detector::Field
