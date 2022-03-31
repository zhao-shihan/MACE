#include "Core/Geometry/Description/SpectrometerMagnet.hxx"

using MACE::Core::Geometry::Description::SpectrometerMagnet;

SpectrometerMagnet& SpectrometerMagnet::Instance() noexcept {
    static SpectrometerMagnet instance;
    return instance;
}
