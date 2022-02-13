#include "Geometry/Description/DescendantsOfWorld/FirstBendSolenoid.hxx"

using namespace MACE::Geometry::Description;

FirstBendSolenoid& FirstBendSolenoid::Instance() {
    static FirstBendSolenoid instance;
    return instance;
}
