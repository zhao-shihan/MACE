#include "Core/Geometry/Description/FirstBendSolenoid.hxx"
#include "Utility/LiteralUnit.hxx"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

FirstBendSolenoid& FirstBendSolenoid::Instance() noexcept {
    static FirstBendSolenoid instance;
    return instance;
}

FirstBendSolenoid::FirstBendSolenoid() :
    IDescription("FirstBendSolenoid"),
    fInnerRadius(7.5_cm),
    fOuterRadius(12.5_cm),
    fBendRadius(50_cm) {}

} // namespace MACE::Core::Geometry::Description
