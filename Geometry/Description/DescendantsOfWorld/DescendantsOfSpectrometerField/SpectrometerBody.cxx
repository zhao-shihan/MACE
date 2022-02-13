#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/SpectrometerBody.hxx"

using namespace MACE::Geometry::Description;

SpectrometerBody& SpectrometerBody::Instance() {
    static SpectrometerBody instance;
    return instance;
}
