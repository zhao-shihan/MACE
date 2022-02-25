#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/SpectrometerMagnet.hxx"

using namespace MACE::Geometry::Description;

SpectrometerMagnet& SpectrometerMagnet::Instance() noexcept {
    static SpectrometerMagnet instance;
    return instance;
}
