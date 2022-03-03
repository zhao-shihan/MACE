#include "Geometry/Description/DescendantsOfWorld/SpectrometerShield.hxx"

using namespace MACE::Geometry::Description;

SpectrometerShield& SpectrometerShield::Instance() noexcept {
    static SpectrometerShield instance;
    return instance;
}
