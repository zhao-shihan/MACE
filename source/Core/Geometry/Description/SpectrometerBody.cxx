#include "Core/Geometry/Description/SpectrometerBody.hxx"
#include "Utility/LiteralUnit.hxx"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

SpectrometerBody& SpectrometerBody::Instance() noexcept {
    static SpectrometerBody instance;
    return instance;
}

SpectrometerBody::SpectrometerBody() :
    IDescription("SpectrometerBody"),
    fGasInnerRadius(15_cm),
    fGasOuterRadius(45_cm),
    fGasInnerLength(90_cm),
    fGasOuterLength(180_cm),
    fShellInnerThickness(1_mm),
    fShellSideThickness(5_mm),
    fShellOuterThickness(10_mm) {}

} // namespace MACE::Core::Geometry::Description
