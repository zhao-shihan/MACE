#include "Geometry/Description/SecondTransportSolenoid.hxx"

using MACE::Geometry::Description::SecondTransportSolenoid;

SecondTransportSolenoid& SecondTransportSolenoid::Instance() noexcept {
    static SecondTransportSolenoid instance;
    return instance;
}
