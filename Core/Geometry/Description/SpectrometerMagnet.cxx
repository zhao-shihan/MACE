#include "Core/Geometry/Description/SpectrometerMagnet.hxx"
#include "Utility/LiteralUnit.hxx"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

SpectrometerMagnet& SpectrometerMagnet::Instance() noexcept {
    static SpectrometerMagnet instance;
    return instance;
}

SpectrometerMagnet::SpectrometerMagnet() :
    IDescription("SpectrometerMagnet"),
    fInnerRadius(50_cm),
    fOuterRadius(70_cm),
    fLength(218_cm) {}

} // namespace MACE::Core::Geometry::Description
