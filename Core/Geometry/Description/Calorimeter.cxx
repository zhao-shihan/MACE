#include "Core/Geometry/Description/Calorimeter.hxx"

using MACE::Core::Geometry::Description::Calorimeter;

Calorimeter& Calorimeter::Instance() noexcept {
    static Calorimeter instance;
    return instance;
}
