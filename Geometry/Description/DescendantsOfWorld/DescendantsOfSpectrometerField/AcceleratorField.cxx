#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/AcceleratorField.hxx"

using namespace MACE::Geometry::Description;

AcceleratorField& AcceleratorField::Instance() noexcept {
    static AcceleratorField instance;
    return instance;
}
