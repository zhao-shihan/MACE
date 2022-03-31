#include "Core/Geometry/Description/SecondBendSolenoid.hxx"
#include "Utility/LiteralUnit.hxx"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

SecondBendSolenoid& SecondBendSolenoid::Instance() noexcept {
    static SecondBendSolenoid instance;
    return instance;
}

SecondBendSolenoid::SecondBendSolenoid() :
    IDescription("SecondBendSolenoid"),
    fInnerRadius(7.5_cm),
    fOuterRadius(12.5_cm),
    fBendRadius(50_cm) {}

} // namespace MACE::Core::Geometry::Description