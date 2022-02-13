#include "Geometry/Description/DescendantsOfWorld/DescendantsOfCalorimeterField/Calorimeter.hxx"

using namespace MACE::Geometry::Description;

Calorimeter& Calorimeter::Instance() {
    static Calorimeter instance;
    return instance;
}
