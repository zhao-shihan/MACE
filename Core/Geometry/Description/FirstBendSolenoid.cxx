#include "Core/Geometry/Description/FirstBendSolenoid.hxx"

using MACE::Geometry::Description::FirstBendSolenoid;

FirstBendSolenoid& FirstBendSolenoid::Instance() noexcept {
    static FirstBendSolenoid instance;
    return instance;
}
