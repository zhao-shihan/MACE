#include "Core/Geometry/Description/SpectrometerMagnet.hxx"

using MACE::Geometry::Description::SpectrometerMagnet;

SpectrometerMagnet& SpectrometerMagnet::Instance() noexcept {
    static SpectrometerMagnet instance;
    return instance;
}
