#include "MACE/Detector/Description/EMC2.h++"
#include "MACE/Math/Hypot.h++"
#include "MACE/Utility/LiteralUnit.h++"
#include "MACE/Utility/MathConstant.h++"
#include "MACE/Utility/PhysicalConstant.h++"

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
using namespace LiteralUnit::Time;
using namespace LiteralUnit::Energy;
using namespace PhysicalConstant;

EMC::EMC() :
    DescriptionSingletonBase{__func__},
    fNSubdivision{2},
    fInnerRadius{15_cm},
    fCrystalLength{15_cm},
    fPMTRadius{2.54_cm},
    fPMTCouplerThickness{0.1_mm},
    fPMTWindowThickness{1_mm},
    fPMTCathodeThickness{20_nm},
    fCouplerEnergyBin{8.01532E-07, 1.89386E-06, 1.92915E-06, 2.1093E-06,
                      2.27541E-06, 2.55633E-06, 2.58828E-06},
    fCouplerRefractiveIndex{1.3912, 1.3992, 1.3997, 1.4015, 1.4034, 1.4071, 1.4076},
    fPMTWaveLengthBin{626.176, 605.811, 586.416, 569.93, 560.987, 552.613, 546.656, 540.699,
                      533.218, 526.292, 518.534, 510.776, 502.802, 494.29, 486.532, 478.774,
                      471.016, 463.397, 456.47, 448.712, 439.984, 431.741, 420.589, 407.013,
                      388.588, 367.253, 348.828, 339.885, 332.897, 329.191, 325.446, 321.675,
                      319.736, 317.075, 315.127, 313.296, 311.008, 309.623, 307.37, 305.438,
                      304.22, 302.28, 300.826, 296.462, 292.167, 288.704, 284.049},
    fPMTQuantumEfficiency{0.204, 0.722, 1.743, 2.944, 4.079, 5.358, 6.511, 7.701,
                          8.963, 10.256, 11.55, 12.799, 14.135, 15.525, 16.865, 18.199,
                          19.506, 20.676, 21.839, 22.989, 24.187, 25.301, 26.659, 27.883,
                          29.047, 29.716, 29.256, 27.824, 26.225, 24.677, 22.936, 21.35,
                          19.683, 18.363, 17.153, 15.724, 14.789, 13.7, 12.307, 11.032,
                          9.919, 8.666, 7.293, 5.502, 3.789, 2.28, 0.703},
    fCsIEnergyBin{1.75E-06, 1.77E-06, 1.78E-06, 1.80E-06, 1.82E-06, 1.83E-06, 1.85E-06, 1.87E-06,
                  1.88E-06, 1.89E-06, 1.91E-06, 1.92E-06, 1.93E-06, 1.94E-06, 1.95E-06, 1.96E-06,
                  1.98E-06, 1.98E-06, 2.00E-06, 2.01E-06, 2.02E-06, 2.04E-06, 2.05E-06, 2.07E-06,
                  2.08E-06, 2.09E-06, 2.11E-06, 2.11E-06, 2.13E-06, 2.15E-06, 2.16E-06, 2.18E-06,
                  2.20E-06, 2.22E-06, 2.25E-06, 2.28E-06, 2.32E-06, 2.35E-06, 2.37E-06, 2.39E-06,
                  2.41E-06, 2.43E-06, 2.44E-06, 2.46E-06, 2.47E-06, 2.49E-06, 2.50E-06, 2.52E-06,
                  2.53E-06, 2.55E-06, 2.56E-06, 2.57E-06, 2.59E-06, 2.61E-06, 2.62E-06, 2.65E-06,
                  2.67E-06, 2.69E-06, 2.72E-06, 2.74E-06, 2.77E-06, 2.80E-06, 2.84E-06, 2.87E-06,
                  2.92E-06, 2.98E-06, 3.04E-06, 3.11E-06, 3.18E-06, 3.25E-06, 3.32E-06, 3.40E-06,
                  3.48E-06, 3.57E-06},
    fCsIScintillationComponent1{0.126974051, 0.143090606, 0.16675108, 0.19144027, 0.216129461, 0.240818651, 0.263450409, 0.289682674,
                                0.314886222, 0.341118487, 0.364264603, 0.390188253, 0.415186058, 0.441418323, 0.46147829, 0.48805346,
                                0.515485894, 0.535545861, 0.562121031, 0.589553465, 0.609613432, 0.637491643, 0.666192827, 0.690367659,
                                0.717114282, 0.737174249, 0.762377798, 0.782437765, 0.810315976, 0.837816991, 0.866621046, 0.895082196,
                                0.921828819, 0.948061084, 0.974293348, 0.986295038, 0.974293348, 0.9490898, 0.923886251, 0.899197061,
                                0.869021384, 0.840354491, 0.813813611, 0.789124421, 0.760937595, 0.729973235, 0.698597389, 0.668764618,
                                0.633273906, 0.59932627, 0.558691977, 0.525773057, 0.497295271, 0.466450419, 0.440801093, 0.408499402,
                                0.377295009, 0.349451089, 0.323115952, 0.299661221, 0.272194497, 0.250420003, 0.226930981, 0.203270507,
                                0.181153108, 0.158178444, 0.136918308, 0.117715605, 0.098855806, 0.08136763, 0.063879453, 0.046734182,
                                0.030960533, 0.015186883},
    fScintillationYield{54000_MeV},
    fScintillationTimeConstant1{1000_ns},
    fResolutionScale{1.0} {}

void EMC::ImportValues(const YAML::Node& node) {
    ImportValue(node, fNSubdivision, "NSubdivision");
    ImportValue(node, fInnerRadius, "InnerRadius");
    ImportValue(node, fCrystalLength, "CrystalLength");
    ImportValue(node, fPMTRadius, "PMTRadius");
    ImportValue(node, fPMTCouplerThickness, "PMTCouplerThickness");
    ImportValue(node, fPMTWindowThickness, "PMTWindowThickness");
    ImportValue(node, fPMTCathodeThickness, "PMTCathodeThickness");

    ImportValue(node, fCouplerEnergyBin, "fCouplerEnergyBin");
    ImportValue(node, fCouplerRefractiveIndex, "fCouplerRefractiveIndex");
    ImportValue(node, fCsIEnergyBin, "fCsIEnergyBin");
    ImportValue(node, fCsIScintillationComponent1, "fCsIScintillationComponent1");

    ImportValue(node, fScintillationYield, "fScintillationYield");
    ImportValue(node, fScintillationTimeConstant1, "fScintillationTimeConstant1");
    ImportValue(node, fResolutionScale, "fReolutionScale");
}

void EMC::ExportValues(YAML::Node& node) const {
    ExportValue(node, fNSubdivision, "NSubdivision");
    ExportValue(node, fInnerRadius, "InnerRadius");
    ExportValue(node, fCrystalLength, "CrystalLength");
    ExportValue(node, fPMTRadius, "PMTRadius");
    ExportValue(node, fPMTCouplerThickness, "PMTCouplerThickness");
    ExportValue(node, fPMTWindowThickness, "PMTWindowThickness");
    ExportValue(node, fPMTCathodeThickness, "PMTCathodeThickness");

    ExportValue(node, fCouplerEnergyBin, "fCouplerEnergyBin");
    ExportValue(node, fCouplerRefractiveIndex, "fCouplerRefractiveIndex");
    ExportValue(node, fCsIEnergyBin, "fCsIEnergyBin");
    ExportValue(node, fCsIScintillationComponent1, "fCsIScintillationComponent1");

    ExportValue(node, fScintillationYield, "fScintillationYield");
    ExportValue(node, fScintillationTimeConstant1, "fScintillationTimeConstant1");
    ExportValue(node, fResolutionScale, "fReolutionScale");
}

} // namespace MACE::Detector::Description
