#include "Geometry/Description/DescendantsOfWorld/SpectrometerShield.hxx"

using namespace MACE::Geometry::Description;

SpectrometerShield& SpectrometerShield::Instance() {
    static SpectrometerShield instance;
    return instance;
}
