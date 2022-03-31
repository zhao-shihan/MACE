#include "Core/Geometry/Description/Collimator.hxx"

using MACE::Core::Geometry::Description::Collimator;

Collimator& Collimator::Instance() noexcept {
    static Collimator instance;
    return instance;
}
