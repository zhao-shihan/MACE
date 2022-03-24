#include "Geometry/Description/ThirdTransportSolenoid.hxx"

using MACE::Geometry::Description::ThirdTransportSolenoid;

ThirdTransportSolenoid& ThirdTransportSolenoid::Instance() noexcept {
    static ThirdTransportSolenoid instance;
    return instance;
}
