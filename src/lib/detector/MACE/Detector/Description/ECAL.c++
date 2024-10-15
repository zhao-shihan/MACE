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

ECAL::ECAL() : // clang-format off
    DescriptionBase{"ECAL"}, // clang-format on
    fNSubdivision{3},
    fInnerRadius{20_cm},
    fCrystalHypotenuse{10_cm},
    fUpstreamWindowRadius{50_mm},
    fDownstreamWindowRadius{5_mm},
    fPMTDimensions{{29.3_mm, 25_mm, 87_mm},    // 9442B Type-HEX01
                   {29.3_mm, 25_mm, 87_mm},    // 9442B Type-PEN
                   {39.9_mm, 32_mm, 98.5_mm},  // 9902B Type-HEX02
                   {39.9_mm, 32_mm, 98.5_mm},  // 9902B Type-HEX03
                   {39.9_mm, 32_mm, 98.5_mm},  // 9902B Type-HEX04
                   {39.9_mm, 32_mm, 98.5_mm},  // 9902B Type-HEX05
                   {39.9_mm, 32_mm, 98.5_mm},  // 9902B Type-HEX06
                   {39.9_mm, 32_mm, 98.5_mm},  // 9902B Type-HEX07
                   {39.9_mm, 32_mm, 98.5_mm},  // 9902B Type-HEX08
                   {39.9_mm, 32_mm, 98.5_mm}}, // 9902B Type-HEX09
    fPMTCouplerThickness{0.1_mm},
    fPMTWindowThickness{1_mm},
    fPMTCathodeThickness{20_nm},
    fPMTWaveLengthBin{1.732649965_eV, 1.760237951_eV, 1.803307489_eV, 1.848537542_eV, 1.896094863_eV, 1.946160761_eV,
                      1.997657575_eV, 2.045172376_eV, 2.092877718_eV, 2.123492226_eV, 2.145831664_eV, 2.168816794_eV,
                      2.18850057_eV, 2.204563937_eV, 2.221286508_eV, 2.242202221_eV, 2.265173439_eV, 2.290315074_eV,
                      2.319490762_eV, 2.352989916_eV, 2.387857013_eV, 2.422646099_eV, 2.453711564_eV, 2.48323493_eV,
                      2.511441394_eV, 2.542243582_eV, 2.574809989_eV, 2.617165988_eV, 2.665600148_eV, 2.716592531_eV,
                      2.794890081_eV, 2.902336797_eV, 3.021316555_eV, 3.150468334_eV, 3.291154851_eV, 3.444993614_eV,
                      3.568086447_eV, 3.6351373_eV, 3.69352408_eV, 3.729691757_eV, 3.773692253_eV, 3.806938806_eV,
                      3.836048038_eV, 3.8701779_eV, 3.893115743_eV, 3.918282138_eV, 3.954402073_eV, 3.973712174_eV,
                      4.006861856_eV, 4.035218382_eV, 4.0587919_eV, 4.097020153_eV, 4.111990233_eV, 4.142952897_eV,
                      4.181888035_eV, 4.215921914_eV, 4.248868735_eV, 4.293483423_eV, 4.340214275_eV, 4.411684499_eV},
    fPMTQuantumEfficiency{0.02127199, 0.023711999, 0.026882652, 0.036106808, 0.063807859, 0.108120481, 0.164142098, 0.224122019,
                          0.280902734, 0.337209838, 0.394250583, 0.449404618, 0.499867939, 0.550845507, 0.601264213, 0.647937451,
                          0.692802533, 0.731277522, 0.765258316, 0.795359882, 0.825909201, 0.855388828, 0.885355595, 0.910628675,
                          0.933195916, 0.953840352, 0.974005647, 0.986363486, 0.994735037, 1, 0.978012287, 0.931522654, 0.873218372, 0.809931614, 0.739391423, 0.660306577, 0.590867405, 0.548180896, 0.508035701, 0.47757201, 0.442859497,
                          0.413233409, 0.386846022, 0.357928411, 0.332676414, 0.307558758, 0.278592853, 0.250487697, 0.221780137,
                          0.19695136, 0.173669539, 0.151310592, 0.131968497, 0.110316789, 0.091042209, 0.073968316, 0.057868983,
                          0.040410736, 0.023812707, 0.007422319}, // ET 9269B

    // fMPPCWaveLengthBin{1.399343529_eV,1.423461833_eV,1.448429481_eV,1.474286883_eV,1.50108428_eV,1.529222646_eV,
    //                    1.557273673_eV,1.587666707_eV,1.618794136_eV,1.651164329_eV,1.684860095_eV,1.719959789_eV,
    //                    1.756859093_eV,1.785918703_eV,1.815894654_eV,1.853349881_eV,1.886077079_eV,1.915929061_eV,
    //                    1.944659315_eV,1.974264333_eV,2.004787926_eV,2.046056415_eV,2.081653772_eV,2.119471168_eV,
    //                    2.149584536_eV,2.18056977_eV,2.212461343_eV,2.245299612_eV,2.279127365_eV,2.312479827_eV,
    //                    2.352057228_eV,2.396485748_eV,2.433756974_eV,2.470083586_eV,2.508672631_eV,2.553623941_eV,
    //                    2.610148394_eV,2.695343321_eV,2.786243586_eV,2.883462234_eV,2.970172311_eV,3.078679432_eV,
    //                    3.208950281_eV,3.30402668_eV,3.479812132_eV,3.698006632_eV,3.879281694_eV,3.998464679_eV,
    //                    4.103377923_eV,4.147358761_eV,4.185501153_eV,4.206569565_eV,4.256174282_eV,4.287872093_eV,
    //                    4.396451409_eV},
    // fMPPCEfficiency{0.308838385,0.351521313,0.390753224,0.426631123,0.459248787,0.505718309,0.531996526,0.559806671,
    //                 0.594897565,0.626023408,0.658043431,0.690517115,0.714064485,0.745791351,0.766203261,0.786409362,
    //                 0.816022856,0.838386119,0.859994663,0.879218925,0.899462063,0.921327714,0.936606989,0.948356626,
    //                 0.959781398,0.966615108,0.971894952,0.978328958,0.983136572,0.987652327,0.991132783,0.994504324,
    //                 0.998310652,1,0.999367717,0.999528778,0.980377731,0.934180164,0.877682103,0.811414246,0.751019262,
    //                 0.676327249,0.58598677,0.519508678,0.440601892,0.366556485,0.308987501,0.267305589,0.223481945,
    //                 0.195327884,0.16646857,0.139742696,0.061575328,0.037278118,0.017382126}, // S14161

    fMPPCNPixelRows{4,
                    4,
                    8,
                    8,
                    8,
                    8,
                    8,
                    8,
                    8,
                    8},
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

    fMPPCWaveLengthBin{1.399343529_eV, 1.423461833_eV, 1.448429481_eV, 1.474286883_eV, 1.50108428_eV, 1.529222646_eV,
                       1.557273673_eV, 1.587666707_eV, 1.618794136_eV, 1.651164329_eV, 1.684860095_eV, 1.719959789_eV,
                       1.756859093_eV, 1.785918703_eV, 1.815894654_eV, 1.853349881_eV, 1.886077079_eV, 1.915929061_eV,
                       1.944659315_eV, 1.974264333_eV, 2.004787926_eV, 2.046056415_eV, 2.081653772_eV, 2.119471168_eV,
                       2.149584536_eV, 2.18056977_eV, 2.212461343_eV, 2.245299612_eV, 2.279127365_eV, 2.312479827_eV,
                       2.352057228_eV, 2.396485748_eV, 2.433756974_eV, 2.470083586_eV, 2.508672631_eV, 2.553623941_eV,
                       2.610148394_eV, 2.695343321_eV, 2.786243586_eV, 2.883462234_eV, 2.970172311_eV, 3.078679432_eV,
                       3.208950281_eV, 3.30402668_eV, 3.479812132_eV, 3.698006632_eV, 3.879281694_eV, 3.998464679_eV,
                       4.103377923_eV, 4.147358761_eV, 4.185501153_eV, 4.206569565_eV, 4.256174282_eV, 4.287872093_eV,
                       4.396451409_eV},
    fMPPCEfficiency{0.308838385, 0.351521313, 0.390753224, 0.426631123, 0.459248787, 0.505718309, 0.531996526, 0.559806671,
                    0.594897565, 0.626023408, 0.658043431, 0.690517115, 0.714064485, 0.745791351, 0.766203261, 0.786409362,
                    0.816022856, 0.838386119, 0.859994663, 0.879218925, 0.899462063, 0.921327714, 0.936606989, 0.948356626,
                    0.959781398, 0.966615108, 0.971894952, 0.978328958, 0.983136572, 0.987652327, 0.991132783, 0.994504324,
                    0.998310652, 1, 0.999367717, 0.999528778, 0.980377731, 0.934180164, 0.877682103, 0.811414246, 0.751019262,
                    0.676327249, 0.58598677, 0.519508678, 0.440601892, 0.366556485, 0.308987501, 0.267305589, 0.223481945,
                    0.195327884, 0.16646857, 0.139742696, 0.061575328, 0.037278118, 0.017382126}, // S13361
    // crystal
    // CsI(Tl) optical param.s
    //  fScintillationWavelengthBin{1.75799786_eV, 1.77994996_eV, 1.798603934_eV, 1.814143751_eV, 1.834661538_eV,
    //                              1.854466567_eV, 1.871980063_eV, 1.882407862_eV, 1.891871096_eV, 1.9032009_eV,
    //                              1.912954443_eV, 1.919168532_eV, 1.929448247_eV, 1.942512233_eV, 1.957597106_eV,
    //                              1.973052378_eV, 1.99079904_eV, 2.001754016_eV, 2.015391308_eV, 2.031355015_eV,
    //                              2.039344883_eV, 2.056438174_eV, 2.077661038_eV, 2.099202424_eV, 2.111386578_eV,
    //                              2.123928411_eV, 2.14165019_eV, 2.157194248_eV, 2.177243502_eV, 2.199544809_eV,
    //                              2.221873462_eV, 2.241107796_eV, 2.265552557_eV, 2.301438711_eV, 2.320361683_eV,
    //                              2.352131729_eV, 2.37818109_eV, 2.398657992_eV, 2.417997543_eV, 2.4350292_eV,
    //                              2.447113349_eV, 2.46226055_eV, 2.481227603_eV, 2.495264837_eV, 2.511680217_eV,
    //                              2.522142178_eV, 2.532615016_eV, 2.540069295_eV, 2.547989951_eV, 2.556769856_eV,
    //                              2.565294866_eV, 2.580187488_eV, 2.595618836_eV, 2.614675154_eV, 2.633448624_eV,
    //                              2.651264738_eV, 2.680903307_eV, 2.7098411_eV, 2.733867481_eV, 2.766990476_eV,
    //                              2.798657607_eV, 2.826185215_eV, 2.854229888_eV, 2.905139416_eV, 2.936450905_eV,
    //                              2.980792838_eV, 3.027886973_eV, 3.069223313_eV, 3.119525362_eV, 3.206875253_eV,
    //                              3.297147101_eV, 3.392648364_eV, 3.435270008_eV, 3.486493614_eV, 3.539734543_eV},
    //  fScintillationComponent1{0.2150343, 0.267627536, 0.3048431, 0.335741304, 0.371059827, 0.409039656, 0.446381903,
    //                           0.46813153, 0.495083691, 0.529738038, 0.550832655, 0.565467074, 0.589952361, 0.621692317,
    //                           0.655108408, 0.688325138, 0.722308299, 0.747319235, 0.767846023, 0.79510255, 0.807751346,
    //                           0.834502956, 0.862454636, 0.887007446, 0.907103039, 0.923078238, 0.944492848, 0.961622732,
    //                           0.977981917, 0.990576074, 0.996575861, 1, 0.988476466, 0.954773117, 0.924315762, 0.87551017,
    //                           0.827330587, 0.783231037, 0.74496324, 0.711244629, 0.685453048, 0.64941831, 0.610222584,
    //                           0.577439209, 0.540798204, 0.516580095, 0.494012241, 0.475615699, 0.458182987, 0.432024974,
    //                           0.411226748, 0.385863922, 0.357909097, 0.331185777, 0.308196968, 0.285724644, 0.253893645,
    //                           0.227946156, 0.205844265, 0.17997558, 0.160086789, 0.143901583, 0.130765912, 0.11061005,
    //                           0.100902905, 0.088571923, 0.076606632, 0.067955003, 0.057204844, 0.042829261, 0.030170677,
    //                           0.019236068, 0.014921883, 0.00993115, 0.005730789},
    //  fScintillationYield{54000},
    //  fScintillationTimeConstant1{1000_ns},

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
        std::cout << ">>--->>edgeLengthSet" << "\n";
        for (int type{1}; auto&& pair : edgeLengthSet) {
            std::ranges::sort(pair.second);
            std::cout << "--->>type " << type << " : " << "\n";
            std::cout << ">>lengths: " << "\n";
            for (auto&& value : pair.first) {
                std::cout << value << " ";
            }
            std::cout << "\n>>units(" << pair.second.size() << "units total): " << "\n";
            for (auto&& value : pair.second) {
                std::cout << value << " ";
            }
            std::cout << "\n";
            std::cout << "======================================================\n";
            type++;
        }
    // }
    //

    int typeID{};
    for (auto&& pair : edgeLengthSet) {
        for (auto&& value : pair.second) {
            typeMap[value] = typeID;//unitID->typeID
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
