#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/SpectrometerBody.hxx"

using namespace MACE::Geometry::Description;

SpectrometerBody& SpectrometerBody::Instance() noexcept {
    static SpectrometerBody instance;
    return instance;
}
