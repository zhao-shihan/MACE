#include "Geometry/Description/DescendantsOfWorld/SecondBendSolenoid.hxx"

using namespace MACE::Geometry::Description;

SecondBendSolenoid& SecondBendSolenoid::Instance() {
    static SecondBendSolenoid instance;
    return instance;
}
