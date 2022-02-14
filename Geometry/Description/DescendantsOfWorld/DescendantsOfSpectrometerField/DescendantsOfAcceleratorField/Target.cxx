#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfAcceleratorField/Target.hxx"

using namespace MACE::Geometry::Description;

Target& Target::Instance() noexcept {
    static Target instance;
    return instance;
}
