#include "Geometry/Description/DescendantsOfWorld/DescendantsOfFirstBendField/FirstBendSolenoid.hxx"

using namespace MACE::Geometry::Description;

FirstBendSolenoid& FirstBendSolenoid::Instance() noexcept {
    static FirstBendSolenoid instance;
    return instance;
}
