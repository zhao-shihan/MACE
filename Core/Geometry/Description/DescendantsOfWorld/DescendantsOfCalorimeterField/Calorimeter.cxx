#include "Geometry/Description/DescendantsOfWorld/DescendantsOfCalorimeterField/Calorimeter.hxx"

using namespace MACE::Geometry::Description;

Calorimeter& Calorimeter::Instance() noexcept {
    static Calorimeter instance;
    return instance;
}
