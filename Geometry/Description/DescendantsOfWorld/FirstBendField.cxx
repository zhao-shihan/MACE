#include "Geometry/Description/DescendantsOfWorld/FirstBendField.hxx"

using namespace MACE::Geometry::Description;

FirstBendField& FirstBendField::Instance() {
    static FirstBendField instance;
    return instance;
}
