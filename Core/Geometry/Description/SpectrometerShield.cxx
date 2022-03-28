#include "Core/Geometry/Description/SpectrometerShield.hxx"

using MACE::Geometry::Description::SpectrometerShield;

SpectrometerShield& SpectrometerShield::Instance() noexcept {
    static SpectrometerShield instance;
    return instance;
}
