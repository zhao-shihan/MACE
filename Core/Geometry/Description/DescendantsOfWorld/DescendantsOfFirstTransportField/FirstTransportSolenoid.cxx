#include "Geometry/Description/DescendantsOfWorld/DescendantsOfFirstTransportField/FirstTransportSolenoid.hxx"

using namespace MACE::Geometry::Description;

FirstTransportSolenoid& FirstTransportSolenoid::Instance() noexcept {
    static FirstTransportSolenoid instance;
    return instance;
}
