#include "Geometry/Description/DescendantsOfWorld/FirstTransportSolenoid.hxx"

using namespace MACE::Geometry::Description;

FirstTransportSolenoid& FirstTransportSolenoid::Instance() {
    static FirstTransportSolenoid instance;
    return instance;
}
