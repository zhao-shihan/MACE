#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSecondTransportField/SelectorField.hxx"

using namespace MACE::Geometry::Description;

SelectorField& SelectorField::Instance() noexcept {
    static SelectorField instance;
    return instance;
}
