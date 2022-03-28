#include "Core/Geometry/Description/SecondBendSolenoid.hxx"

using MACE::Geometry::Description::SecondBendSolenoid;

SecondBendSolenoid& SecondBendSolenoid::Instance() noexcept {
    static SecondBendSolenoid instance;
    return instance;
}
