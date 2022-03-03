#include "Geometry/Description/DescendantsOfWorld/DescendantsOfCalorimeterField/VertexDetector.hxx"

using namespace MACE::Geometry::Description;

VertexDetector& VertexDetector::Instance() noexcept {
    static VertexDetector instance;
    return instance;
}
