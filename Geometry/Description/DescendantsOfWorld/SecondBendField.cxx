#include "Geometry/Description/DescendantsOfWorld/SecondBendField.hxx"

using namespace MACE::Geometry::Description;

SecondBendField& SecondBendField::Instance() noexcept {
    static SecondBendField instance;
    return instance;
}
