#include "Core/Geometry/Description/SecondTransportSolenoid.hxx"

using MACE::Core::Geometry::Description::SecondTransportSolenoid;

SecondTransportSolenoid& SecondTransportSolenoid::Instance() noexcept {
    static SecondTransportSolenoid instance;
    return instance;
}
