#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSecondTransportField/SelectorField.hxx"

using namespace MACE::Geometry::Description;

SelectorField& SelectorField::Instance() {
    static SelectorField instance;
    return instance;
}
