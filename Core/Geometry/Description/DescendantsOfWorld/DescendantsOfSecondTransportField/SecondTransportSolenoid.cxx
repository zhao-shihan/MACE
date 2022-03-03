#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSecondTransportField/SecondTransportSolenoid.hxx"

using namespace MACE::Geometry::Description;

SecondTransportSolenoid& SecondTransportSolenoid::Instance() noexcept {
    static SecondTransportSolenoid instance;
    return instance;
}
