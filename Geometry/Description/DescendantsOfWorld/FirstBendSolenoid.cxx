#include "Geometry/Description/DescendantsOfWorld/FirstBendSolenoid.hxx"

using namespace MACE::Geometry::Description;

FirstBendSolenoid& FirstBendSolenoid::Instance() noexcept {
    static FirstBendSolenoid instance;
    return instance;
}
