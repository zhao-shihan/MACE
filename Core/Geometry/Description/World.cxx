#include "Core/Geometry/Description/World.hxx"
#include "Utility/LiteralUnit.hxx"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

World& World::Instance() noexcept {
    static World instance;
    return instance;
}

World::World() :
    IDescription("World"),
    fHalfXExtent(3_m),
    fHalfYExtent(1_m),
    fHalfZExtent(4_m) {}

} // namespace MACE::Core::Geometry::Description
