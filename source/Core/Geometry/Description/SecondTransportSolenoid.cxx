#include "Core/Geometry/Description/SecondTransportSolenoid.hxx"
#include "Utility/LiteralUnit.hxx"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

SecondTransportSolenoid& SecondTransportSolenoid::Instance() noexcept {
    static SecondTransportSolenoid instance;
    return instance;
}

SecondTransportSolenoid::SecondTransportSolenoid() :
    IDescription("SecondTransportSolenoid"),
    fInnerRadius(7.5_cm),
    fOuterRadius(12.5_cm),
    fLength(100_cm) {}

} // namespace MACE::Core::Geometry::Description
