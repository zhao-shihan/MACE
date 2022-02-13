#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/AcceleratorField.hxx"

using namespace MACE::Geometry::Description;

AcceleratorField& AcceleratorField::Instance() {
    static AcceleratorField instance;
    return instance;
}
