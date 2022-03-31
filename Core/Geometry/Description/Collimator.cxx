#include "Core/Geometry/Description/Collimator.hxx"
#include "Utility/LiteralUnit.hxx"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

Collimator& Collimator::Instance() noexcept {
    static Collimator instance;
    return instance;
}

Collimator::Collimator() :
    IDescription("Collimator"),
    fInnerRadius(5_mm),
    fOuterRadius(65_mm),
    fLength(30_cm),
    fZPosition(-20_cm),
    fThickness(0.75_mm),
    fCount(7) {}

} // namespace MACE::Core::Geometry::Description
