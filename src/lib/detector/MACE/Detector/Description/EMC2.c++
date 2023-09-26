#include "MACE/Detector/Description/EMC2.h++"
#include "MACE/Math/Hypot.h++"
#include "MACE/Utility/LiteralUnit.h++"
#include "MACE/Utility/MathConstant.h++"

#include "pmp/algorithms/subdivision.h"
#include "pmp/surface_mesh.h"

#include <ranges>

namespace MACE::Detector::Description {

namespace {

using namespace MathConstant;

class EMCMesh {
private:
    struct Data {
    private:
        struct VertexPair {
            Eigen::Vector3d inner;
            Eigen::Vector3d outer;
        };

    public:
        std::vector<VertexPair> vertex;
        std::vector<std::vector<gsl::index>> face;
    };

public:
    EMCMesh(const EMC& emc);
    auto Generate() && -> Data;

private:
    auto GenerateIcosahedron() -> void;
    auto GenerateIcosphere() -> void;
    auto GenerateDualMesh() -> void;
    auto GenerateData() const -> Data;

private:
    pmp::SurfaceMesh fMesh;
    const EMC& fEMC;
};

EMCMesh::EMCMesh(const EMC& emc) :
    fMesh{},
    fEMC{emc} {}

auto EMCMesh::Generate() && -> Data {
    GenerateIcosahedron();
    GenerateIcosphere();
    GenerateDualMesh();
    return GenerateData();
}

auto EMCMesh::GenerateIcosahedron() -> void {
    // vertices coordinates (not normalized)
    constexpr auto a0 = 1.0;
    constexpr auto b0 = 1.0 / phi;
    // normalized vertices coordinates
    const auto a = a0 / Math::Hypot(a0, b0);
    const auto b = b0 / Math::Hypot(a0, b0);

    // add normalized vertices
    const auto v1 = fMesh.add_vertex(pmp::Point{0, b, -a});
    const auto v2 = fMesh.add_vertex(pmp::Point{b, a, 0});
    const auto v3 = fMesh.add_vertex(pmp::Point{-b, a, 0});
    const auto v4 = fMesh.add_vertex(pmp::Point{0, b, a});
    const auto v5 = fMesh.add_vertex(pmp::Point{0, -b, a});
    const auto v6 = fMesh.add_vertex(pmp::Point{-a, 0, b});
    const auto v7 = fMesh.add_vertex(pmp::Point{0, -b, -a});
    const auto v8 = fMesh.add_vertex(pmp::Point{a, 0, -b});
    const auto v9 = fMesh.add_vertex(pmp::Point{a, 0, b});
    const auto v10 = fMesh.add_vertex(pmp::Point{-a, 0, -b});
    const auto v11 = fMesh.add_vertex(pmp::Point{b, -a, 0});
    const auto v12 = fMesh.add_vertex(pmp::Point{-b, -a, 0});

    // add triangles
    fMesh.add_triangle(v3, v2, v1);
    fMesh.add_triangle(v2, v3, v4);
    fMesh.add_triangle(v6, v5, v4);
    fMesh.add_triangle(v5, v9, v4);
    fMesh.add_triangle(v8, v7, v1);
    fMesh.add_triangle(v7, v10, v1);
    fMesh.add_triangle(v12, v11, v5);
    fMesh.add_triangle(v11, v12, v7);
    fMesh.add_triangle(v10, v6, v3);
    fMesh.add_triangle(v6, v10, v12);
    fMesh.add_triangle(v9, v8, v2);
    fMesh.add_triangle(v8, v9, v11);
    fMesh.add_triangle(v3, v6, v4);
    fMesh.add_triangle(v9, v2, v4);
    fMesh.add_triangle(v10, v3, v1);
    fMesh.add_triangle(v2, v8, v1);
    fMesh.add_triangle(v12, v10, v7);
    fMesh.add_triangle(v8, v11, v7);
    fMesh.add_triangle(v6, v12, v5);
    fMesh.add_triangle(v11, v9, v5);
}

auto EMCMesh::GenerateIcosphere() -> void {
    // do division
    for (auto i = 0; i < fEMC.NSubdivision(); ++i) {
        // do sub-division
        pmp::loop_subdivision(fMesh);
        // project to unit sphere
        for (auto&& v : fMesh.vertices()) {
            fMesh.position(v).normalize();
        }
    }
}

auto EMCMesh::GenerateDualMesh() -> void {
    // the new dual mesh
    pmp::SurfaceMesh dualMesh;

    // a property to remember new vertices per face
    auto faceVertex = fMesh.add_face_property<pmp::Vertex>("f:vertex");

    // for each face add the centroid to the dual mesh
    for (auto&& f : fMesh.faces()) {
        pmp::Point centroid{0, 0, 0};
        pmp::Scalar n{0};
        for (auto&& v : fMesh.vertices(f)) {
            centroid += fMesh.position(v);
            ++n;
        }
        centroid /= n;
        faceVertex[f] = dualMesh.add_vertex(centroid);
    }

    // add new face for each vertex
    for (auto&& v : fMesh.vertices()) {
        std::vector<pmp::Vertex> vertices;
        vertices.reserve(6);
        for (auto&& f : fMesh.faces(v)) {
            vertices.emplace_back(faceVertex[f]);
        }
        dualMesh.add_face(std::move(vertices));
    }

    // swap old and new meshes, don't copy properties
    fMesh.assign(dualMesh);
}

auto EMCMesh::GenerateData() const -> Data {
    Data data;
    data.vertex.reserve(fMesh.n_vertices());
    data.face.reserve(fMesh.n_faces());

    for (const auto point = fMesh.get_vertex_property<pmp::Point>("v:point");
         auto&& f : fMesh.faces()) {
        auto& face = data.face.emplace_back();
        for (auto&& v : fMesh.vertices(f)) {
            data.vertex.push_back({point[v] * fEMC.InnerRadius(),
                                   point[v] * (fEMC.InnerRadius() + fEMC.CrystalLength())});
            face.emplace_back(v.idx());
        }
    }

    return data;
}

} // namespace

using namespace LiteralUnit::Length;

EMC::EMC() :
    DescriptionSingletonBase{__func__},
    fInnerRadius{15_cm},
    fCrystalLength{5_cm},
    fWindowRadius{8_cm} {}

void EMC::ImportValues(const YAML::Node& node) {
    ImportValue(node, fNSubdivision, "NSubdivision");
    ImportValue(node, fInnerRadius, "InnerRadius");
    ImportValue(node, fCrystalLength, "CrystalLength");
    ImportValue(node, fWindowRadius, "WindowRadius");
}

void EMC::ExportValues(YAML::Node& node) const {
    ExportValue(node, fNSubdivision, "NSubdivision");
    ExportValue(node, fInnerRadius, "InnerRadius");
    ExportValue(node, fCrystalLength, "CrystalLength");
    ExportValue(node, fWindowRadius, "WindowRadius");
}

} // namespace MACE::Detector::Description
