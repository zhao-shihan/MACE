#include "Core/Geometry/Description/SpectrometerBody.hxx"

using MACE::Core::Geometry::Description::SpectrometerBody;

SpectrometerBody& SpectrometerBody::Instance() noexcept {
    static SpectrometerBody instance;
    return instance;
}
