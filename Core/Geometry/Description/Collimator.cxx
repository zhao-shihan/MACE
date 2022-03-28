#include "Core/Geometry/Description/Collimator.hxx"

using MACE::Geometry::Description::Collimator;

Collimator& Collimator::Instance() noexcept {
    static Collimator instance;
    return instance;
}
