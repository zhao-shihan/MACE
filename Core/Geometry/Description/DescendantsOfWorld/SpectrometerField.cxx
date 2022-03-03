#include "Geometry/Description/DescendantsOfWorld/SpectrometerField.hxx"

using namespace MACE::Geometry::Description;

SpectrometerField& SpectrometerField::Instance() noexcept {
    static SpectrometerField instance;
    return instance;
}
