#include "Core/Geometry/Description/VertexDetector.hxx"
#include "Utility/LiteralUnit.hxx"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

VertexDetector& VertexDetector::Instance() noexcept {
    static VertexDetector instance;
    return instance;
}

VertexDetector::VertexDetector() :
    IDescription("VertexDetector"),
    fWidth(15_cm),
    fThickness(1_cm) {}

} // namespace MACE::Core::Geometry::Description
