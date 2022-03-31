#include "Core/Geometry/Description/FirstBendSolenoid.hxx"

using MACE::Core::Geometry::Description::FirstBendSolenoid;

FirstBendSolenoid& FirstBendSolenoid::Instance() noexcept {
    static FirstBendSolenoid instance;
    return instance;
}
