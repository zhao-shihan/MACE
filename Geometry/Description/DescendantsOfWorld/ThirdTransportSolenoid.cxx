#include "Geometry/Description/DescendantsOfWorld/ThirdTransportSolenoid.hxx"

using namespace MACE::Geometry::Description;

ThirdTransportSolenoid& ThirdTransportSolenoid::Instance() noexcept {
    static ThirdTransportSolenoid instance;
    return instance;
}
