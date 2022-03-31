#include "Core/Geometry/Description/ThirdTransportSolenoid.hxx"

using MACE::Core::Geometry::Description::ThirdTransportSolenoid;

ThirdTransportSolenoid& ThirdTransportSolenoid::Instance() noexcept {
    static ThirdTransportSolenoid instance;
    return instance;
}
