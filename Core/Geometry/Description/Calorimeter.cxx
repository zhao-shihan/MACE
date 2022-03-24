#include "Geometry/Description/Calorimeter.hxx"

using MACE::Geometry::Description::Calorimeter;

Calorimeter& Calorimeter::Instance() noexcept {
    static Calorimeter instance;
    return instance;
}
