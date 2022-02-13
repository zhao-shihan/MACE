#include "Geometry/Description/DescendantsOfWorld/SecondTransportSolenoid.hxx"

using namespace MACE::Geometry::Description;

SecondTransportSolenoid& SecondTransportSolenoid::Instance() {
    static SecondTransportSolenoid instance;
    return instance;
}
