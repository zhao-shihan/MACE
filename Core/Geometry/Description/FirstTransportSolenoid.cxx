#include "Core/Geometry/Description/FirstTransportSolenoid.hxx"

using MACE::Geometry::Description::FirstTransportSolenoid;

FirstTransportSolenoid& FirstTransportSolenoid::Instance() noexcept {
    static FirstTransportSolenoid instance;
    return instance;
}
