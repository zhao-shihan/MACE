#include "Core/Geometry/Description/VertexDetector.hxx"

using MACE::Geometry::Description::VertexDetector;

VertexDetector& VertexDetector::Instance() noexcept {
    static VertexDetector instance;
    return instance;
}
