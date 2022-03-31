#include "Core/Geometry/Description/FirstTransportSolenoid.hxx"

using MACE::Core::Geometry::Description::FirstTransportSolenoid;

FirstTransportSolenoid& FirstTransportSolenoid::Instance() noexcept {
    static FirstTransportSolenoid instance;
    return instance;
}
