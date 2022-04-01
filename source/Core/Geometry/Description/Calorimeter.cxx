#include "Core/Geometry/Description/Calorimeter.hxx"
#include "Utility/LiteralUnit.hxx"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

Calorimeter& Calorimeter::Instance() noexcept {
    static Calorimeter instance;
    return instance;
}

Calorimeter::Calorimeter() :
    IDescription("Calorimeter"),
    fInnerRadius(15_cm),
    fInnerLength(50_cm),
    fWindowRadius(8_cm),
    fCrystalLength(5_cm) {}

} // namespace MACE::Core::Geometry::Description
