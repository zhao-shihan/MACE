#include "MACE/Detector/Description/EMC.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Math/Hypot.h++"
#include "MACE/Utility/LiteralUnit.h++"
#include "MACE/Utility/MathConstant.h++"
#include "MACE/Utility/PhysicalConstant.h++"
#include "MACE/Utility/VectorCast.h++"

#include "CLHEP/Vector/TwoVector.h"

#include "G4SystemOfUnits.hh"
#include "G4Transform3D.hh"

#include "pmp/algorithms/differential_geometry.h"
#include "pmp/algorithms/normals.h"
#include "pmp/algorithms/subdivision.h"
#include "pmp/algorithms/utilities.h"
#include "pmp/surface_mesh.h"

#include <ranges>

namespace MACE::Detector::Description {

namespace {

using namespace MathConstant;

class EMCMesh {
public:
    EMCMesh(int n);
    auto Generate() && -> auto;

private:
    auto GenerateIcosahedron() -> void;
    auto GenerateIcosphere() -> void;
    auto GenerateDualMesh() -> void;

private:
    pmp::SurfaceMesh fPMPMesh;
    const int fNSubdivision;
};

EMCMesh::EMCMesh(int n) :
    fPMPMesh{},
    fNSubdivision{n} {}

auto EMCMesh::Generate() && -> auto {
    GenerateIcosahedron();
    GenerateIcosphere();
    GenerateDualMesh();
    return fPMPMesh;
}

auto EMCMesh::GenerateIcosahedron() -> void {
    // vertices coordinates (not normalized)
    constexpr auto a0 = 1.0;
    constexpr auto b0 = 1.0 / phi;
    // normalized vertices coordinates
    const auto a = a0 / Math::Hypot(a0, b0);
    const auto b = b0 / Math::Hypot(a0, b0);

    // add normalized vertices
    const auto v1 = fPMPMesh.add_vertex(pmp::Point{0, b, -a});
    const auto v2 = fPMPMesh.add_vertex(pmp::Point{b, a, 0});
    const auto v3 = fPMPMesh.add_vertex(pmp::Point{-b, a, 0});
    const auto v4 = fPMPMesh.add_vertex(pmp::Point{0, b, a});
    const auto v5 = fPMPMesh.add_vertex(pmp::Point{0, -b, a});
    const auto v6 = fPMPMesh.add_vertex(pmp::Point{-a, 0, b});
    const auto v7 = fPMPMesh.add_vertex(pmp::Point{0, -b, -a});
    const auto v8 = fPMPMesh.add_vertex(pmp::Point{a, 0, -b});
    const auto v9 = fPMPMesh.add_vertex(pmp::Point{a, 0, b});
    const auto v10 = fPMPMesh.add_vertex(pmp::Point{-a, 0, -b});
    const auto v11 = fPMPMesh.add_vertex(pmp::Point{b, -a, 0});
    const auto v12 = fPMPMesh.add_vertex(pmp::Point{-b, -a, 0});

    // add triangles
    fPMPMesh.add_triangle(v3, v2, v1);
    fPMPMesh.add_triangle(v2, v3, v4);
    fPMPMesh.add_triangle(v6, v5, v4);
    fPMPMesh.add_triangle(v5, v9, v4);
    fPMPMesh.add_triangle(v8, v7, v1);
    fPMPMesh.add_triangle(v7, v10, v1);
    fPMPMesh.add_triangle(v12, v11, v5);
    fPMPMesh.add_triangle(v11, v12, v7);
    fPMPMesh.add_triangle(v10, v6, v3);
    fPMPMesh.add_triangle(v6, v10, v12);
    fPMPMesh.add_triangle(v9, v8, v2);
    fPMPMesh.add_triangle(v8, v9, v11);
    fPMPMesh.add_triangle(v3, v6, v4);
    fPMPMesh.add_triangle(v9, v2, v4);
    fPMPMesh.add_triangle(v10, v3, v1);
    fPMPMesh.add_triangle(v2, v8, v1);
    fPMPMesh.add_triangle(v12, v10, v7);
    fPMPMesh.add_triangle(v8, v11, v7);
    fPMPMesh.add_triangle(v6, v12, v5);
    fPMPMesh.add_triangle(v11, v9, v5);
}

auto EMCMesh::GenerateIcosphere() -> void {
    // do division
    for (auto i = 0; i < fNSubdivision; ++i) {
        // do sub-division
        pmp::loop_subdivision(fPMPMesh);
        // project to unit sphere
        for (auto&& v : fPMPMesh.vertices()) {
            fPMPMesh.position(v).normalize();
        }
    }
}

auto EMCMesh::GenerateDualMesh() -> void {
    // the new dual mesh
    pmp::SurfaceMesh dualMesh;

    // a property to remember new vertices per face
    auto faceVertex = fPMPMesh.add_face_property<pmp::Vertex>("f:vertex");

    // for each face add the centroid to the dual mesh
    for (auto&& f : fPMPMesh.faces()) {
        pmp::Point centroid{0, 0, 0};
        pmp::Scalar n{0};
        for (auto&& v : fPMPMesh.vertices(f)) {
            centroid += fPMPMesh.position(v);
            ++n;
        }
        centroid /= n;
        faceVertex[f] = dualMesh.add_vertex(centroid);
    }

    // add new face for each vertex
    for (auto&& v : fPMPMesh.vertices()) {
        std::vector<pmp::Vertex> vertices;
        vertices.reserve(6);
        for (auto&& f : fPMPMesh.faces(v)) {
            vertices.emplace_back(faceVertex[f]);
        }
        dualMesh.add_face(std::move(vertices));
    }

    // swap old and new meshes, don't copy properties
    fPMPMesh.assign(dualMesh);
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
    fCrystalHypotenuse{10_cm},
    fSmallPMTRadius{25.5_mm},
    fSmallPMTLength{144_mm},
    fSmallPMTCathodeRadius{23_mm},
    fLargePMTRadius{34_mm},
    fLargePMTLength{156_mm},
    fLargePMTCathodeRadius{32_mm},
    fPMTCouplerThickness{0.1_mm},
    fPMTWindowThickness{1_mm},
    fPMTCathodeThickness{20_nm},
    fPMTWaveLengthBin{715.759, 704.541, 687.714, 670.887, 654.06, 637.234, 620.807, 606.384,
                      592.562, 584.019, 577.939, 571.814, 566.671, 562.542, 558.307, 553.099,
                      547.49, 541.48, 534.669, 527.057, 519.361, 511.903, 505.422, 499.413,
                      493.804, 487.821, 481.651, 473.856, 465.246, 456.513, 443.724, 427.297,
                      410.47, 393.643, 376.816, 359.989, 347.57, 341.159, 335.766, 332.51,
                      328.633, 325.763, 323.291, 320.44, 318.552, 316.506, 313.615, 312.091,
                      309.509, 307.334, 305.549, 302.698, 301.596, 299.342, 296.555, 294.161,
                      291.88, 288.847, 285.737, 281.108},
    fPMTQuantumEfficiency{0.206, 0.237, 0.282, 0.398, 0.74, 1.321, 2.113, 3.024,
                          3.969, 4.905, 5.856, 6.819, 7.723, 8.636, 9.57, 10.508,
                          11.467, 12.374, 13.281, 14.205, 15.191, 16.195, 17.195,
                          18.114, 18.987, 19.886, 20.83, 21.794, 22.8, 23.806, 24.644,
                          25.312, 25.713, 25.932, 25.835, 25.279, 24.266, 23.367, 22.357,
                          21.43, 20.344, 19.319, 18.363, 17.294, 16.265, 15.232, 14.053,
                          12.759, 11.486, 10.345, 9.229, 8.193, 7.198, 6.108, 5.136, 4.241,
                          3.37, 2.403, 1.447, 0.466}, // ET 9269B
    fCsIEnergyBin{1.75e-06, 1.77e-06, 1.78e-06, 1.80e-06, 1.82e-06, 1.83e-06, 1.85e-06, 1.87e-06,
                  1.88e-06, 1.89e-06, 1.91e-06, 1.92e-06, 1.93e-06, 1.94e-06, 1.95e-06, 1.96e-06,
                  1.98e-06, 1.98e-06, 2.00e-06, 2.01e-06, 2.02e-06, 2.04e-06, 2.05e-06, 2.07e-06,
                  2.08e-06, 2.09e-06, 2.11e-06, 2.11e-06, 2.13e-06, 2.15e-06, 2.16e-06, 2.18e-06,
                  2.20e-06, 2.22e-06, 2.25e-06, 2.28e-06, 2.32e-06, 2.35e-06, 2.37e-06, 2.39e-06,
                  2.41e-06, 2.43e-06, 2.44e-06, 2.46e-06, 2.47e-06, 2.49e-06, 2.50e-06, 2.52e-06,
                  2.53e-06, 2.55e-06, 2.56e-06, 2.57e-06, 2.59e-06, 2.61e-06, 2.62e-06, 2.65e-06,
                  2.67e-06, 2.69e-06, 2.72e-06, 2.74e-06, 2.77e-06, 2.80e-06, 2.84e-06, 2.87e-06,
                  2.92e-06, 2.98e-06, 3.04e-06, 3.11e-06, 3.18e-06, 3.25e-06, 3.32e-06, 3.40e-06,
                  3.48e-06, 3.57e-06},
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
    fScintillationYield{54000},
    fScintillationTimeConstant1{1000_ns},
    fResolutionScale{1} {}

auto EMC::ComputeMesh() const -> MeshInformation {
    auto pmpMesh = EMCMesh{fNSubdivision}.Generate();
    MeshInformation mesh;
    auto& [vertex, faceList]{mesh};
    const auto solenoidInnerRadius = Solenoid::Instance().InnerRadius();
    const auto point = pmpMesh.vertex_property<pmp::Point>("v:point");

    for (auto&& v : pmpMesh.vertices()) {
        vertex.emplace_back(VectorCast<CLHEP::Hep3Vector>(point[v]));
    }

    for (auto&& f : pmpMesh.faces()) {
        if (std::ranges::any_of(pmpMesh.vertices(f), [&](const auto& v) {
                CLHEP::Hep2Vector p{point[v][0] * fInnerRadius, point[v][1] * fInnerRadius};
                return p.mag() < solenoidInnerRadius and point[v][2] < 0;
            })) {
            continue;
        }

        const auto centroid = VectorCast<CLHEP::Hep3Vector>(pmp::centroid(pmpMesh, f));
        if (centroid.perp2() < 1e-3) {
            continue;
        }

        auto& face = faceList.emplace_back();
        face.centroid = centroid;
        face.normal = VectorCast<CLHEP::Hep3Vector>(pmp::face_normal(pmpMesh, f));

        for (auto&& v : pmpMesh.vertices(f)) {
            face.vertexIndex.emplace_back(v.idx());
        }

        const auto LocalPhi =
            [uHat = (vertex[face.vertexIndex.front()] - face.centroid).unit(),
             vHat = face.normal.cross(vertex[face.vertexIndex.front()] - face.centroid).unit(),
             &localOrigin = face.centroid,
             &vertex = vertex](const auto& i) {
                const auto localPoint = vertex[i] - localOrigin;
                return std::atan2(localPoint.dot(vHat), localPoint.dot(uHat));
            };
        std::ranges::sort(face.vertexIndex,
                          [&LocalPhi](const auto& i, const auto& j) {
                              return LocalPhi(i) < LocalPhi(j);
                          });
    }
    return mesh;
}
auto EMC::ComputeTransformToOuterSurfaceWithOffset(int cellID, double offsetInNormalDirection) const -> HepGeom::Transform3D {
    const auto& faceList = Mesh().fFaceList;
    auto&& [centroid, normal, vertexIndex] = faceList[cellID];

    const auto centroidMagnitude = centroid.mag();
    const auto crystalOuterRadius = (fInnerRadius + fCrystalHypotenuse) * centroidMagnitude;

    auto crystalOuterCentroid = crystalOuterRadius * centroid / centroidMagnitude;
    auto rotation = G4Rotate3D{normal.theta(), CLHEP::HepZHat.cross(normal)};

    return G4Translate3D{crystalOuterCentroid + offsetInNormalDirection * normal} * rotation;
}

auto EMC::ImportValues(const YAML::Node& node) -> void {
    ImportValue(node, fNSubdivision, "NSubdivision");
    ImportValue(node, fInnerRadius, "InnerRadius");
    ImportValue(node, fCrystalHypotenuse, "CrystalHypotenuse");
    ImportValue(node, fSmallPMTRadius, "SmallPMTRadius");
    ImportValue(node, fSmallPMTLength, "SmallPMTLength");
    ImportValue(node, fSmallPMTCathodeRadius, "SmallPMTCathodeRadius");
    ImportValue(node, fLargePMTRadius, "LargePMTRadius");
    ImportValue(node, fLargePMTLength, "LargePMTLength");
    ImportValue(node, fLargePMTCathodeRadius, "LargePMTCathodeRadius");
    ImportValue(node, fPMTCouplerThickness, "PMTCouplerThickness");
    ImportValue(node, fPMTWindowThickness, "PMTWindowThickness");
    ImportValue(node, fPMTCathodeThickness, "PMTCathodeThickness");
    // ImportValue(node, fPMTWaveLengthBin, "PMTWaveLengthBin");
    // ImportValue(node, fPMTQuantumEfficiency, "PMTQuantumEfficiency");
    // ImportValue(node, fCsIEnergyBin, "CsIEnergyBin");
    // ImportValue(node, fCsIScintillationComponent1, "CsIScintillationComponent1");
    // ImportValue(node, fScintillationYield, "ScintillationYield");
    // ImportValue(node, fScintillationTimeConstant1, "ScintillationTimeConstant1");
    // ImportValue(node, fResolutionScale, "ReolutionScale");

    SetGeometryOutdated();
}

auto EMC::ExportValues(YAML::Node& node) const -> void {
    ExportValue(node, fNSubdivision, "NSubdivision");
    ExportValue(node, fInnerRadius, "InnerRadius");
    ExportValue(node, fCrystalHypotenuse, "CrystalHypotenuse");
    ExportValue(node, fSmallPMTRadius, "SmallPMTRadius");
    ExportValue(node, fSmallPMTLength, "SmallPMTLength");
    ExportValue(node, fSmallPMTCathodeRadius, "SmallPMTCathodeRadius");
    ExportValue(node, fLargePMTRadius, "LargePMTRadius");
    ExportValue(node, fLargePMTLength, "LargePMTLength");
    ExportValue(node, fLargePMTCathodeRadius, "LargePMTCathodeRadius");
    ExportValue(node, fPMTCouplerThickness, "PMTCouplerThickness");
    ExportValue(node, fPMTWindowThickness, "PMTWindowThickness");
    ExportValue(node, fPMTCathodeThickness, "PMTCathodeThickness");
    // ExportValue(node, fPMTWaveLengthBin, "PMTWaveLengthBin");
    // ExportValue(node, fPMTQuantumEfficiency, "PMTQuantumEfficiency");
    // ExportValue(node, fCsIEnergyBin, "CsIEnergyBin");
    // ExportValue(node, fCsIScintillationComponent1, "CsIScintillationComponent1");
    // ExportValue(node, fScintillationYield, "ScintillationYield");
    // ExportValue(node, fScintillationTimeConstant1, "ScintillationTimeConstant1");
    // ExportValue(node, fResolutionScale, "ReolutionScale");
}

} // namespace MACE::Detector::Description
