#include "Geometry/Description/DescendantsOfWorld/VertexDetectorShield.hxx"

using namespace MACE::Geometry::Description;

VertexDetectorShield& VertexDetectorShield::Instance() {
    static VertexDetectorShield instance;
    return instance;
}
