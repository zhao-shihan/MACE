#include "Geometry/Description/DescendantsOfWorld/SecondTransportSolenoid.hxx"

using namespace MACE::Geometry::Description;

SecondTransportSolenoid& SecondTransportSolenoid::Instance() noexcept {
    static SecondTransportSolenoid instance;
    return instance;
}
