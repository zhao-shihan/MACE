#include "Core/Geometry/Description/FirstTransportSolenoid.hxx"
#include "Utility/LiteralUnit.hxx"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

FirstTransportSolenoid& FirstTransportSolenoid::Instance() noexcept {
    static FirstTransportSolenoid instance;
    return instance;
}

FirstTransportSolenoid::FirstTransportSolenoid() :
    IDescription("FirstTransportSolenoid"),
    fInnerRadius(7.5_cm),
    fOuterRadius(12.5_cm),
    fLength(20_cm) {}

} // namespace MACE::Core::Geometry::Description
