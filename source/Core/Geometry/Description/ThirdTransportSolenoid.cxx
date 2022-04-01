#include "Core/Geometry/Description/ThirdTransportSolenoid.hxx"
#include "Utility/LiteralUnit.hxx"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

ThirdTransportSolenoid& ThirdTransportSolenoid::Instance() noexcept {
    static ThirdTransportSolenoid instance;
    return instance;
}

ThirdTransportSolenoid::ThirdTransportSolenoid() :
    IDescription("ThirdTransportSolenoid"),
    fInnerRadius(7.5_cm),
    fOuterRadius(12.5_cm),
    fLength(20_cm) {}

} // namespace MACE::Core::Geometry::Description
