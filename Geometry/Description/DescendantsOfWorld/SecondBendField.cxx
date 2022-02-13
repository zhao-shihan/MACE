#include "Geometry/Description/DescendantsOfWorld/SecondBendField.hxx"

using namespace MACE::Geometry::Description;

SecondBendField& SecondBendField::Instance() {
    static SecondBendField instance;
    return instance;
}
