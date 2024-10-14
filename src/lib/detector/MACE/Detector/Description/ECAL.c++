#include "MACE/Detector/Description/ECAL.h++"

#include "Mustard/Utility/LiteralUnit.h++"
#include "Mustard/Utility/MathConstant.h++"
#include "Mustard/Utility/PhysicalConstant.h++"
#include "Mustard/Utility/VectorCast.h++"

#include "CLHEP/Vector/TwoVector.h"

#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4Transform3D.hh"

#include "pmp/algorithms/differential_geometry.h"
#include "pmp/algorithms/normals.h"
#include "pmp/algorithms/subdivision.h"
#include "pmp/algorithms/utilities.h"
#include "pmp/surface_mesh.h"

#include "muc/math"

#include <concepts>
#include <queue>
#include <ranges>

namespace MACE::Detector::Description {

namespace {

static_assert(std::same_as<pmp::Scalar, double>, "PMP should be compiled with PMP_SCALAR_TYPE_64");

using namespace Mustard::MathConstant;

class ECALMesh {
public:
    ECALMesh(int n);
    auto Generate() && -> auto;

private:
    auto GenerateIcosahedron() -> void;
    auto GenerateIcosphere() -> void;
    auto GenerateDualMesh() -> void;

private:
    pmp::SurfaceMesh fPMPMesh;
    const int fNSubdivision;
};

ECALMesh::ECALMesh(int n) :
    fPMPMesh{},
    fNSubdivision{n} {}

auto ECALMesh::Generate() && -> auto {
    GenerateIcosahedron();
    GenerateIcosphere();
    GenerateDualMesh();
    return fPMPMesh;
}

auto ECALMesh::GenerateIcosahedron() -> void {
    // vertices coordinates (not normalized)
    constexpr auto a0 = 1.0;
    constexpr auto b0 = 1.0 / phi;
    // normalized vertices coordinates
    const auto a = a0 / muc::hypot(a0, b0);
    const auto b = b0 / muc::hypot(a0, b0);

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

auto ECALMesh::GenerateIcosphere() -> void {
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

auto ECALMesh::GenerateDualMesh() -> void {
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

using namespace Mustard::LiteralUnit::Length;
using namespace Mustard::LiteralUnit::Time;
using namespace Mustard::LiteralUnit::Energy;
using namespace Mustard::PhysicalConstant;

ECAL::ECAL() :
    DescriptionBase{
        "ECAL"
},
    fNSubdivision{3},
    fInnerRadius{20_cm},
    fCrystalHypotenuse{10_cm},
    fUpstreamWindowRadius{50_mm},
    fDownstreamWindowRadius{5_mm},
    fPMTDimensions{
        {29.3_mm, 25_mm, 87_mm},   // 9442B Type-HEX01
        {29.3_mm, 25_mm, 87_mm},   // 9442B Type-PEN
        {39.9_mm, 32_mm, 98.5_mm}, // 9902B Type-HEX02
        {39.9_mm, 32_mm, 98.5_mm}, // 9902B Type-HEX03
        {39.9_mm, 32_mm, 98.5_mm}, // 9902B Type-HEX04
        {39.9_mm, 32_mm, 98.5_mm}, // 9902B Type-HEX05
        {39.9_mm, 32_mm, 98.5_mm}, // 9902B Type-HEX06
        {39.9_mm, 32_mm, 98.5_mm}, // 9902B Type-HEX07
        {39.9_mm, 32_mm, 98.5_mm}, // 9902B Type-HEX08
        {39.9_mm, 32_mm, 98.5_mm}, // 9902B Type-HEX09
    },
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

    // fMPPCWaveLengthBin{886.244, 871.228, 856.21, 841.193, 826.176, 810.974, 796.366, 781.121, 766.101, 751.082,
    //                    736.061, 721.04, 705.896, 694.41, 682.947, 669.145, 657.534, 647.289, 637.726, 628.163,
    //                    618.599, 606.122, 595.757, 585.127, 576.93, 568.732, 560.534, 552.336, 544.138, 536.29,
    //                    527.266, 517.491, 509.566, 502.072, 494.349, 485.647, 475.13, 460.112, 445.101, 430.094,
    //                    417.538, 402.822, 386.469, 375.348, 356.387, 335.359, 319.688, 310.159, 302.229, 299.024,
    //                    296.299, 294.815, 291.379, 289.225, 282.082},
    // fMPPCEfficiency{0.045, 0.053, 0.061, 0.069, 0.077, 0.088, 0.096, 0.105, 0.116, 0.127,
    //                 0.139, 0.152, 0.164, 0.177, 0.188, 0.201, 0.216, 0.229, 0.242, 0.255,
    //                 0.269, 0.287, 0.302, 0.317, 0.33, 0.342, 0.354, 0.367, 0.38, 0.393,
    //                 0.408, 0.425, 0.44, 0.454, 0.468, 0.485, 0.497, 0.505, 0.507, 0.502,
    //                 0.493, 0.477, 0.449, 0.422, 0.397, 0.373, 0.346, 0.318, 0.28, 0.25,
    //                 0.217, 0.184, 0.083, 0.051, 0.025}, // S14161

    fMPPCNPixelRows{
        4,
        4,
        8,
        8,
        8,
        8,
        8,
        8,
        8,
        8,
    },
    fMPPCPixelSizeSet{3_mm,
                      3_mm,
                      3_mm,
                      3_mm,
                      3_mm,
                      3_mm,
                      3_mm,
                      3_mm,
                      3_mm,
                      3_mm},
    fMPPCPitch{0.2_mm},     // gap between pixels
    fMPPCThickness{0.1_mm}, // cathode
    fMPPCCouplerThickness{0.1_mm},
    fMPPCWindowThickness{0.2_mm},
    // 0.1(epoxy)+0.1(cathode),window change  from epoxy to epoxy&silicon Pixels, may change name "window" later

    fMPPCWaveLengthBin{886.244, 871.228, 856.21, 841.193, 826.176, 810.974, 796.366, 781.121, 766.101, 751.082,
                       736.061, 721.04, 705.896, 694.41, 682.947, 669.145, 657.534, 647.289, 637.726, 628.163,
                       618.599, 606.122, 595.757, 585.127, 576.93, 568.732, 560.534, 552.336, 544.138, 536.29,
                       527.266, 517.491, 509.566, 502.072, 494.349, 485.647, 475.13, 460.112, 445.101, 430.094,
                       417.538, 402.822, 386.469, 375.348, 356.387, 335.359, 319.688, 310.159, 302.229, 299.024,
                       296.299, 294.815, 291.379, 289.225, 282.082},
    fMPPCEfficiency{0.045, 0.053, 0.061, 0.069, 0.077, 0.088, 0.096, 0.105, 0.116, 0.127,
                    0.139, 0.152, 0.164, 0.177, 0.188, 0.201, 0.216, 0.229, 0.242, 0.255,
                    0.269, 0.287, 0.302, 0.317, 0.33, 0.342, 0.354, 0.367, 0.38, 0.393,
                    0.408, 0.425, 0.44, 0.454, 0.468, 0.485, 0.497, 0.505, 0.507, 0.502,
                    0.493, 0.477, 0.449, 0.422, 0.397, 0.373, 0.346, 0.318, 0.28, 0.25,
                    0.217, 0.184, 0.083, 0.051, 0.025}, // S13361
//crystal
    //CsI(Tl) optical param.s
    // fScintillationWavelengthBin{1.75799786_eV, 1.77994996_eV, 1.798603934_eV, 1.814143751_eV, 1.834661538_eV, 
    //                             1.854466567_eV, 1.871980063_eV, 1.882407862_eV, 1.891871096_eV, 1.9032009_eV, 
    //                             1.912954443_eV, 1.919168532_eV, 1.929448247_eV, 1.942512233_eV, 1.957597106_eV, 
    //                             1.973052378_eV, 1.99079904_eV, 2.001754016_eV, 2.015391308_eV, 2.031355015_eV, 
    //                             2.039344883_eV, 2.056438174_eV, 2.077661038_eV, 2.099202424_eV, 2.111386578_eV, 
    //                             2.123928411_eV, 2.14165019_eV, 2.157194248_eV, 2.177243502_eV, 2.199544809_eV, 
    //                             2.221873462_eV, 2.241107796_eV, 2.265552557_eV, 2.301438711_eV, 2.320361683_eV, 
    //                             2.352131729_eV, 2.37818109_eV, 2.398657992_eV, 2.417997543_eV, 2.4350292_eV, 
    //                             2.447113349_eV, 2.46226055_eV, 2.481227603_eV, 2.495264837_eV, 2.511680217_eV, 
    //                             2.522142178_eV, 2.532615016_eV, 2.540069295_eV, 2.547989951_eV, 2.556769856_eV, 
    //                             2.565294866_eV, 2.580187488_eV, 2.595618836_eV, 2.614675154_eV, 2.633448624_eV, 
    //                             2.651264738_eV, 2.680903307_eV, 2.7098411_eV, 2.733867481_eV, 2.766990476_eV, 
    //                             2.798657607_eV, 2.826185215_eV, 2.854229888_eV, 2.905139416_eV, 2.936450905_eV, 
    //                             2.980792838_eV, 3.027886973_eV, 3.069223313_eV, 3.119525362_eV, 3.206875253_eV, 
    //                             3.297147101_eV, 3.392648364_eV, 3.435270008_eV, 3.486493614_eV, 3.539734543_eV},
    // fScintillationComponent1{0.2150343, 0.267627536, 0.3048431, 0.335741304, 0.371059827, 0.409039656, 0.446381903,
    //                          0.46813153, 0.495083691, 0.529738038, 0.550832655, 0.565467074, 0.589952361, 0.621692317, 
    //                          0.655108408, 0.688325138, 0.722308299, 0.747319235, 0.767846023, 0.79510255, 0.807751346, 
    //                          0.834502956, 0.862454636, 0.887007446, 0.907103039, 0.923078238, 0.944492848, 0.961622732, 
    //                          0.977981917, 0.990576074, 0.996575861, 1, 0.988476466, 0.954773117, 0.924315762, 0.87551017, 
    //                          0.827330587, 0.783231037, 0.74496324, 0.711244629, 0.685453048, 0.64941831, 0.610222584, 
    //                          0.577439209, 0.540798204, 0.516580095, 0.494012241, 0.475615699, 0.458182987, 0.432024974, 
    //                          0.411226748, 0.385863922, 0.357909097, 0.331185777, 0.308196968, 0.285724644, 0.253893645, 
    //                          0.227946156, 0.205844265, 0.17997558, 0.160086789, 0.143901583, 0.130765912, 0.11061005, 
    //                          0.100902905, 0.088571923, 0.076606632, 0.067955003, 0.057204844, 0.042829261, 0.030170677, 
    //                          0.019236068, 0.014921883, 0.00993115, 0.005730789},
    // fScintillationYield{54000},
    // fScintillationTimeConstant1{1000_ns},

    // BGO optical param.s
    fScintillationWavelengthBin{1.945507481_eV, 1.956691365_eV, 1.974526166_eV, 1.992686315_eV, 2.011182111_eV, 
                                2.030023135_eV, 2.049218172_eV, 2.068776498_eV, 2.088712977_eV, 2.109036_eV, 
                                2.12975713_eV, 2.150887751_eV, 2.171451222_eV, 2.190391881_eV, 2.209663573_eV, 
                                2.229274743_eV, 2.247116958_eV, 2.265244608_eV, 2.283666187_eV, 2.301276603_eV, 
                                2.318032238_eV, 2.333890214_eV, 2.349966255_eV, 2.368619281_eV, 2.389971082_eV, 
                                2.412936123_eV, 2.437596391_eV, 2.464039018_eV, 2.492373025_eV, 2.521380095_eV, 
                                2.551089015_eV, 2.581526478_eV, 2.612727511_eV, 2.644717279_eV, 2.677523383_eV, 
                                2.708082211_eV, 2.733054836_eV, 2.75369941_eV, 2.773041191_eV, 2.792667214_eV, 
                                2.810903696_eV, 2.827691812_eV, 2.844122034_eV, 2.861882767_eV, 2.877806421_eV, 
                                2.894720751_eV, 2.911600212_eV, 2.929633378_eV, 2.947486552_eV, 2.965972235_eV, 
                                2.984688528_eV, 3.003641613_eV, 3.024116133_eV, 3.04551166_eV, 3.067869957_eV, 
                                3.091903493_eV, 3.118356404_eV, 3.147344518_eV, 3.178997019_eV, 3.215638088_eV, 
                                3.253129005_eV, 3.281477983_eV, 3.302608153_eV},
    fScintillationComponent1{0.195254826, 0.214876564, 0.247266504, 0.281705118, 0.316502611, 0.351368412, 0.387289114,
                             0.424968103, 0.459795422, 0.494441782, 0.528656318, 0.562776635, 0.595129123, 0.628156693, 
                             0.66160206, 0.695627571, 0.726322943, 0.757562051, 0.788164087, 0.818063582, 0.846719321, 
                             0.873933468, 0.900421966, 0.925228448, 0.945965637, 0.963539434, 0.978127738, 0.991670468, 
                             0.999665211, 1, 0.991116414, 0.973225812, 0.943719198, 0.904954051, 0.858628733, 0.81043525, 
                             0.766603628, 0.72769847, 0.690508334, 0.650827878, 0.615158969, 0.582925251, 0.549468551, 
                             0.518706558, 0.485613932, 0.454237279, 0.422103766, 0.389336957, 0.357120837, 0.324825964, 
                             0.293908848, 0.263908054, 0.234764495, 0.208390636, 0.1828993, 0.156768192, 0.13171465, 
                             0.107656381, 0.084704457, 0.061552239, 0.040184081, 0.024471847, 0.012727081},
    fScintillationYield{10000},
    fScintillationTimeConstant1{300_ns},


    fResolutionScale{1} {}

auto ECAL::ComputeMesh() const -> MeshInformation {
    auto pmpMesh{ECALMesh{fNSubdivision}.Generate()};
    MeshInformation mesh;
    auto& [vertex, faceList, typeMap, clusterMap]{mesh};
    const auto point{pmpMesh.vertex_property<pmp::Point>("v:point")};

    for (auto&& v : pmpMesh.vertices()) {
        vertex.emplace_back(Mustard::VectorCast<CLHEP::Hep3Vector>(point[v]));
    }

    for (auto&& f : pmpMesh.faces()) {
        const auto centroid{Mustard::VectorCast<CLHEP::Hep3Vector>(pmp::centroid(pmpMesh, f))};
        if (const auto rXY{fInnerRadius * centroid.perp()};
            centroid.z() < 0) {
            if (rXY < fUpstreamWindowRadius) { continue; }
        } else {
            if (rXY < fDownstreamWindowRadius) { continue; }
        }
        if (std::ranges::any_of(pmpMesh.vertices(f),
                                [&](const auto& v) {
                                    const auto rXY{fInnerRadius * muc::hypot(point[v][0], point[v][1])};
                                    if (point[v][2] < 0) {
                                        return rXY < fUpstreamWindowRadius;
                                    } else {
                                        return rXY < fDownstreamWindowRadius;
                                    }
                                })) {
            continue;
        }

        auto& face{faceList.emplace_back()};
        face.centroid = centroid;
        face.normal = Mustard::VectorCast<CLHEP::Hep3Vector>(pmp::face_normal(pmpMesh, f));

        for (auto&& v : pmpMesh.vertices(f)) {
            face.vertexIndex.emplace_back(v.idx());
        }

        const auto LocalPhi{
            [uHat = (vertex[face.vertexIndex.front()] - face.centroid).unit(),
             vHat = face.normal.cross(vertex[face.vertexIndex.front()] - face.centroid).unit(),
             &localOrigin = face.centroid,
             &vertex = vertex](const auto& i) {
                const auto localPoint = vertex[i] - localOrigin;
                return std::atan2(localPoint.dot(vHat), localPoint.dot(uHat));
            }};
        std::ranges::sort(face.vertexIndex,
                          [&LocalPhi](const auto& i, const auto& j) {
                              return LocalPhi(i) < LocalPhi(j);
                          });
    }

    std::map<std::vector<float>, std::vector<int>> edgeLengthSet;

    for (int moduleID{};
         auto&& [centroid, _, vertexIndex] : std::as_const(faceList)) { // module types and clusters sorting
        // sort by edge length
        std::vector<float> edgeLength; // magic conversion (double to float)
        std::vector<G4ThreeVector> xV{vertexIndex.size()};

        std::ranges::transform(vertexIndex, xV.begin(),
                               [&](const auto& i) { return vertex[i]; });

        for (int i{}; i < std::ssize(xV); ++i) {
            edgeLength.emplace_back(i != std::ssize(xV) - 1 ? (xV[i + 1] - xV[i]).mag() :
                                                              (xV[0] - xV[i]).mag());
        };

        std::ranges::sort(edgeLength);
        edgeLengthSet[edgeLength].emplace_back(moduleID);

        // sort by centroid distance to other faces
        std::pair<float, int> clusterInfo;

        auto cmp = [](
                       const std::pair<float, int>& p,
                       const std::pair<float, int>& q) { return p.first > q.first; };

        std::priority_queue<std::pair<float, int>,
                            std::vector<std::pair<float, int>>,
                            decltype(cmp)>
            centroidPriority(cmp);

        for (int i{}; auto&& [adjacentCentroid, _1, _2] : std::as_const(faceList)) {
            if (centroid == adjacentCentroid) {
                i++;
                continue;
            }
            clusterInfo.first = (centroid - adjacentCentroid).mag();
            clusterInfo.second = i;
            centroidPriority.push(clusterInfo);
            i++;
        }

        for (int i{}; i < std::ssize(vertexIndex); ++i) {
            auto top = centroidPriority.top();
            if (top.first > 0.2) { continue; }
            clusterMap[moduleID].emplace_back(top.second);
            centroidPriority.pop();
        }
        moduleID++;
    }

    //
    // {
    //     std::cout << ">>--->>edgeLengthSet" << "\n";
    //     for (int type{1}; auto&& pair : edgeLengthSet) {
    //         std::ranges::sort(pair.second);
    //         std::cout << "--->>type " << type << " : " << "\n";
    //         std::cout << ">>lengths: " << "\n";
    //         for (auto&& value : pair.first) {
    //             std::cout << value << " ";
    //         }
    //         std::cout << "\n>>units(" << pair.second.size() << "units total): " << "\n";
    //         for (auto&& value : pair.second) {
    //             std::cout << value << " ";
    //         }
    //         std::cout << "\n";
    //         std::cout << "======================================================\n";
    //         type++;
    //     }
    // }
    //

    int typeID{};
    for (auto&& pair : edgeLengthSet) {
        for (auto&& value : pair.second) {
            typeMap[value] = typeID;
        }
        typeID++;
    }

    return mesh;
}

auto ECAL::ComputeTransformToOuterSurfaceWithOffset(int moduleID, double offsetInNormalDirection) const -> HepGeom::Transform3D {
    const auto& faceList{Mesh().fFaceList};
    auto&& [centroid, normal, vertexIndex]{faceList[moduleID]};

    const auto centroidMagnitude{centroid.mag()};
    const auto crystalOuterRadius{(fInnerRadius + fCrystalHypotenuse) * centroidMagnitude};

    const auto crystalOuterCentroid{crystalOuterRadius * centroid / centroidMagnitude};
    const G4Rotate3D rotation{normal.theta(), CLHEP::HepZHat.cross(normal)};

    return G4Translate3D{crystalOuterCentroid + offsetInNormalDirection * normal} * rotation;
}

auto ECAL::ImportAllValue(const YAML::Node& node) -> void {
    ImportValue(node, fNSubdivision, "NSubdivision");
    ImportValue(node, fInnerRadius, "InnerRadius");
    ImportValue(node, fCrystalHypotenuse, "CrystalHypotenuse");
    ImportValue(node, fUpstreamWindowRadius, "UpstreamWindowRadius");
    ImportValue(node, fDownstreamWindowRadius, "DownstreamWindowRadius");
    ImportValue(node, fPMTDimensions, "PMTDimensions");
    ImportValue(node, fPMTCouplerThickness, "PMTCouplerThickness");
    ImportValue(node, fPMTWindowThickness, "PMTWindowThickness");
    ImportValue(node, fPMTCathodeThickness, "PMTCathodeThickness");
    ImportValue(node, fPMTWaveLengthBin, "PMTWaveLengthBin");
    ImportValue(node, fPMTQuantumEfficiency, "PMTQuantumEfficiency");
    ImportValue(node, fMPPCNPixelRows, "MPPCNPixelRows");
    ImportValue(node, fMPPCPixelSizeSet,
                "MPPCPixelSizeSet");
    ImportValue(node, fMPPCPitch, "MPPCPitch");
    ImportValue(node, fMPPCThickness, "MPPCThickness");
    ImportValue(node, fMPPCCouplerThickness, "MPPCCouplerThickness");
    ImportValue(node, fMPPCWindowThickness, "MPPCWindowThickness");
    ImportValue(node, fMPPCWaveLengthBin, "MPPCWaveLengthBin");
    ImportValue(node, fMPPCEfficiency, "MPPCEfficiency");
    ImportValue(node, fScintillationWavelengthBin, "ScintillationWavelengthBin");
    ImportValue(node, fScintillationComponent1, "ScintillationComponent1");
    ImportValue(node, fScintillationYield, "ScintillationYield");
    ImportValue(node, fScintillationTimeConstant1, "ScintillationTimeConstant1");
    ImportValue(node, fResolutionScale, "ResolutionScale");

    SetGeometryOutdated();
}

auto ECAL::ExportAllValue(YAML::Node& node) const -> void {
    ExportValue(node, fNSubdivision, "NSubdivision");
    ExportValue(node, fInnerRadius, "InnerRadius");
    ExportValue(node, fCrystalHypotenuse, "CrystalHypotenuse");
    ExportValue(node, fUpstreamWindowRadius, "UpstreamWindowRadius");
    ExportValue(node, fDownstreamWindowRadius, "DownstreamWindowRadius");
    ExportValue(node, fPMTDimensions, "PMTDimensions");
    ExportValue(node, fPMTCouplerThickness, "PMTCouplerThickness");
    ExportValue(node, fPMTWindowThickness, "PMTWindowThickness");
    ExportValue(node, fPMTCathodeThickness, "PMTCathodeThickness");
    ExportValue(node, fPMTWaveLengthBin, "PMTWaveLengthBin");
    ExportValue(node, fPMTQuantumEfficiency, "PMTQuantumEfficiency");
    ExportValue(node, fMPPCNPixelRows, "MPPCNPixelRows");
    ExportValue(node, fMPPCPixelSizeSet,
                "MPPCPixelSizeSet");
    ExportValue(node, fMPPCPitch, "MPPCPitch");
    ExportValue(node, fMPPCThickness, "MPPCThickness");
    ExportValue(node, fMPPCCouplerThickness, "MPPCCouplerThickness");
    ExportValue(node, fMPPCWindowThickness, "MPPCWindowThickness");
    ExportValue(node, fMPPCWaveLengthBin, "MPPCWaveLengthBin");
    ExportValue(node, fMPPCEfficiency, "MPPCEfficiency");
    ExportValue(node, fScintillationWavelengthBin, "ScintillationWavelengthBin");
    ExportValue(node, fScintillationComponent1, "ScintillationComponent1");
    ExportValue(node, fScintillationYield, "ScintillationYield");
    ExportValue(node, fScintillationTimeConstant1, "ScintillationTimeConstant1");
    ExportValue(node, fResolutionScale, "ResolutionScale");
}

} // namespace MACE::Detector::Description
