#include "Core/Geometry/Description/SelectorField.hxx"
#include "Utility/LiteralUnit.hxx"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

SelectorField& SelectorField::Instance() noexcept {
    static SelectorField instance;
    return instance;
}

SelectorField::SelectorField() :
    IDescription("SelectorField"),
    fRadius(7.5_cm),
    fLength(30_cm),
    fZPosition(20_cm) {}

} // namespace MACE::Core::Geometry::Description
