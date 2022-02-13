#include "Geometry/Description/DescendantsOfWorld/ThirdTransportSolenoid.hxx"

using namespace MACE::Geometry::Description;

ThirdTransportSolenoid& ThirdTransportSolenoid::Instance() {
    static ThirdTransportSolenoid instance;
    return instance;
}
