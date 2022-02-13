#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSecondTransportField/Collimator.hxx"

using namespace MACE::Geometry::Description;

Collimator& Collimator::Instance() {
    static Collimator instance;
    return instance;
}
