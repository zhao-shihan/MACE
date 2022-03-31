#include "Core/Geometry/Description/SecondBendSolenoid.hxx"

using MACE::Core::Geometry::Description::SecondBendSolenoid;

SecondBendSolenoid& SecondBendSolenoid::Instance() noexcept {
    static SecondBendSolenoid instance;
    return instance;
}
