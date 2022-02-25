#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSecondBendField/SecondBendSolenoid.hxx"

using namespace MACE::Geometry::Description;

SecondBendSolenoid& SecondBendSolenoid::Instance() noexcept {
    static SecondBendSolenoid instance;
    return instance;
}
