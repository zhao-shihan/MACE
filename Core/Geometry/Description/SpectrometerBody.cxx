#include "Geometry/Description/SpectrometerBody.hxx"

using MACE::Geometry::Description::SpectrometerBody;

SpectrometerBody& SpectrometerBody::Instance() noexcept {
    static SpectrometerBody instance;
    return instance;
}
