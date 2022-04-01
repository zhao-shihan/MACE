#include "Core/Geometry/Description/SpectrometerField.hxx"
#include "Utility/LiteralUnit.hxx"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

SpectrometerField& SpectrometerField::Instance() noexcept {
    static SpectrometerField instance;
    return instance;
}

SpectrometerField::SpectrometerField() :
    IDescription("SpectrometerField"),
    fRadius(71_cm),
    fLength(220_cm) {}

} // namespace MACE::Core::Geometry::Description
