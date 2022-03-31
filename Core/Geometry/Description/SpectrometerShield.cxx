#include "Core/Geometry/Description/SpectrometerShield.hxx"
#include "Utility/LiteralUnit.hxx"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

SpectrometerShield& SpectrometerShield::Instance() noexcept {
    static SpectrometerShield instance;
    return instance;
}

SpectrometerShield::SpectrometerShield() :
    IDescription("SpectrometerShield"),
    fInnerRadius(72_cm),
    fInnerLength(222_cm),
    fWindowRadius(12.7_cm),
    fThickness(5_cm) {}

} // namespace MACE::Core::Geometry::Description
