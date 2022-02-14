#include "Geometry/Description/DescendantsOfWorld/SecondTransportField.hxx"

using namespace MACE::Geometry::Description;

SecondTransportField& SecondTransportField::Instance() noexcept {
    static SecondTransportField instance;
    return instance;
}
